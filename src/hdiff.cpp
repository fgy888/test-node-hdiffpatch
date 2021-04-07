/**
 * Created by housisong on 2021.04.07.
 */
#include "hdiff.h"
#include "HDiffPatch/libHDiffPatch/HDiff/diff.h"

#define _CompressPlugin_lzma2
#define _IsNeedIncludeDefaultCompressHead 0
#include "lzma/C/LzmaEnc.h"
#include "lzma/C/Lzma2Enc.h"
#include "lzma/C/MtCoder.h"
#include "HDiffPatch/compress_plugin_demo.h"

void hdiff(const uint8_t* old,size_t oldsize,const uint8_t* _new,size_t newsize,
 	 	       std::vector<uint8_t>& out_codeBuf){
    const int myBestSingleMatchScore=3;
    const size_t myBestStepMemSize=kDefaultStepMemSize;
    const size_t myBestDictSize=(1<<20)*8; //8MB mem

    TCompressPlugin_lzma2 compressPlugin=lzma2CompressPlugin;
    compressPlugin.compress_level=9;
    compressPlugin.dict_size=myBestDictSize;
    compressPlugin.thread_num=1;
    create_single_compressed_diff(_new,_new+newsize,old,old+oldsize,out_codeBuf,0,
                                  &compressPlugin.base,myBestSingleMatchScore,myBestStepMemSize);
}