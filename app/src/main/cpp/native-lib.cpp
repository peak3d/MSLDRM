#include <jni.h>
#include <string>
#include <sstream>
#include <media/NdkMediaDrm.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_peak3d_msldrm_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::stringstream hello;

#if 0

    const uint8_t uuid[] = {0xed,0xef,0x8b,0xa9,0x79,0xd6,0x4a,0xce,0xa3,0xc8,0x27,0xdc,0xd5,0x1d,0x21,0xed};
    AMediaDrm *mediaDrm = AMediaDrm_createByUUID(uuid);

    AMediaDrmSessionId sessionId;
    media_status_t status = AMediaDrm_openSession(mediaDrm, &sessionId);

    hello << "SessionId: " << std::string((const char *)sessionId.ptr, sessionId.length) << "Status:" << status << std::endl;

    AMediaDrmKeySetId ksid;
    ksid.ptr = (const uint8_t*)"ksid1F0269A6";
    ksid.length = 12;

    status = AMediaDrm_restoreKeys(mediaDrm, &sessionId, &ksid);

    hello << "Restore: Status:" << status << std::endl;

    const uint8_t data[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    uint8_t result[16];
    char key[16] = {'1','5','2','3','5','6','6','8','4','8','7','8','2',0,0,0};
    char hmacKey[16] = {'1','5','2','3','5','6','9','9','9','0','3','7','5',0,0,0};
    uint8_t iv[16] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};

    status = AMediaDrm_encrypt(mediaDrm, &sessionId, "AES/CBC/NoPadding", (uint8_t*)key, iv, data, result, 16);

    hello << "Encrypt: Status:" << status << std::endl;

    uint8_t signature[256];
    size_t signature_size(256);
    status = AMediaDrm_sign(mediaDrm, &sessionId, "HmacSHA256", (uint8_t*)hmacKey, result, 16, signature, &signature_size);

    hello << "Sign: Status:" << status << " Sig_size:" << signature_size << std::endl;

    status = AMediaDrm_removeKeys(mediaDrm, &sessionId);

    hello << "Remove: Status:" << status << "Sessionid:" << std::string((const char *)sessionId.ptr, sessionId.length) << std::endl;

    status = AMediaDrm_closeSession(mediaDrm, &sessionId);

    hello << "Close: Status:" << status << std::endl;

    AMediaDrm_release(mediaDrm);
#endif
    hello << "Finished";

    return env->NewStringUTF(hello.str().c_str());
}
