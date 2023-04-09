#include "___blockchainEvent.h"
#include "st_rsa.h"
#include "IUtils.h"
#include "__crc32.h"
#include "mutexInspector.h"

/* Contents of file asasij.pub */
//const long int asasij_pub_size = 162;
//const unsigned char asasij_pub[162] = {
//    0x30, 0x81, 0x9F, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01,
//    0x05, 0x00, 0x03, 0x81, 0x8D, 0x00, 0x30, 0x81, 0x89, 0x02, 0x81, 0x81, 0x00, 0xAF, 0x52, 0x3F,
//    0xEA, 0x97, 0xBA, 0x28, 0xCA, 0x2A, 0x47, 0x4A, 0x85, 0x07, 0x70, 0x8D, 0xE4, 0xDD, 0x8E, 0x9B,
//    0x35, 0x89, 0xA1, 0x44, 0x03, 0x1B, 0x90, 0xB7, 0xEC, 0xE3, 0x62, 0x0C, 0xCE, 0xA0, 0xC8, 0xA1,
//    0x8E, 0xAE, 0x9E, 0x65, 0x3B, 0xCD, 0x01, 0xA5, 0x74, 0x89, 0x83, 0xA0, 0xAB, 0x9D, 0xEA, 0xC1,
//    0x7E, 0x92, 0xDD, 0x70, 0x39, 0x12, 0x0C, 0xC5, 0xD0, 0x5F, 0x17, 0xF6, 0x20, 0x5E, 0x72, 0x83,
//    0x57, 0xF3, 0x62, 0xAD, 0xB0, 0x48, 0x8D, 0x8D, 0x4D, 0xA9, 0x8B, 0xCE, 0xB2, 0x72, 0xAB, 0xD8,
//    0xF3, 0xFA, 0x61, 0xFA, 0x79, 0xEE, 0x41, 0x15, 0xDD, 0x60, 0xD2, 0x77, 0xD7, 0x1A, 0xEF, 0x3E,
//    0xB8, 0x22, 0xE3, 0xD3, 0xDC, 0x37, 0xFC, 0xF5, 0x40, 0x0C, 0x5F, 0xC2, 0x05, 0x24, 0x68, 0x12,
//    0xE6, 0x59, 0xE2, 0xA6, 0xE3, 0xF0, 0xBB, 0xF4, 0xCD, 0x63, 0x53, 0x45, 0x0F, 0x02, 0x03, 0x01,
//    0x00, 0x01
//};
std::string root_public_key="30820222300d06092a864886f70d01010105000382020f003082020a0282020100d46a739a06b6a79b6c9a3a2a921c148fd9cc2c28ac139d8fad951f0e2450a421494f83829e9faac16e794d38b8eb3ffeb08eeb"
"a919c863dc9e64def76f151bc36072c18814ef008c36c28b82bbb8d8bfe22521132c44034f10f1068ef2e20fa31fc8764c84482ac35a442c99061f98882ad83ba4230acc210c882a23ba0ebcc98f0e33a292e2480b96556864d"
"40e28b8cf7e3fdf9a1c06ce66687567efe8fbdeacf39d6ff84681c8943a063658f5cbe674396d8e0ea0aecf960eaaa770695fe3713343bb824c5a6c10cbbbe2379bc1d49d3c987610e7e8355c1e4d956af0896be0b9a6575527"
"294abd6663c41e2399cc104f5eac426b5315d12d8ed2066a98be74732e57b9f60ce17269f9572ab2c21c97c21bd245063f9ddfe57e94660ac7384e0d88c3bbb24d0fadda3678fe632549da5c9067c666c6918d7e58abd2073b1"
"5fecaf08b27130f57d3d12febb89be9ae24594938fd3433ebc86e92de2581eb072bb372b401ffdda7bb4f2517aa667c22a545d78d29b2b204c809d707b1356458e842a3432d177b97fd1a0bb8503dfde652eb3a35cf35f01e46"
"e98a79efab806936adaa9f1981cf0edd26c09fc31cc23e33b10d5ceca57920dfb62100a500efcad583e91543b4e48194625e611c3eb7fd575c62c7b07ff7d2387a0967e94197fcb3f5901c9b5b31e9d1a69199eca0663e68f0a"
"93854e803b93aa9aa30f220f3cf0203010001";

std::string blockchainData::KeyStore::dump()
{
    outBuffer o;
    o<<*this;
    std::string s_64=iUtils->Base64Encode(o.asString()->asString());
    return "keystore@"+s_64;


}
void blockchainData::KeyStore::initFromB64(const std::string &buffer)
{

    std::string b=iUtils->Base64Decode(buffer);
    inBuffer in(b);
    in>>*this;


}

outBuffer& operator<< (outBuffer& b,const blockchainData::KeyStore::Document& s)
{
    b<<s.encryptedPrivateKey;
    b<<s.md5_PrivateKey;
    b<<s.publicKey;
    b<<(int64_t)s.createDate;
    b<<s.name;
    return b;
}
inBuffer& operator>> (inBuffer& b,  blockchainData::KeyStore::Document& s)
{
    b>>s.encryptedPrivateKey;
    b>>s.md5_PrivateKey;
    b>>s.publicKey;
    int64_t  dt;
    b>>dt;
    s.createDate=dt;
    b>>s.name;
    return b;

}
outBuffer& operator<< (outBuffer& b,const blockchainData::KeyStore& s)
{
    b<<s.document;
    b<<s.hash_sha256;
    return b;
}
inBuffer& operator>> (inBuffer& b,  blockchainData::KeyStore& s)
{
    b>>s.document;
    b>>s.hash_sha256;
    return b;
}
std::string blockchainData::KeyStore::getPrivateKey(const std::string& privKeyPassword)
{


    I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);

    st_AES aes;

    aes.init(privKeyPassword);

    std::string privKey=aes.decrypt(toRef(document.encryptedPrivateKey.toString()))->asString();

    if(ssl->md5(privKey)!=document.md5_PrivateKey)
    {

        throw CommonError("Wrong password for private key");
    }
    else logErr2("priv key OK");

    return privKey;

}
std::string blockchainData::KeyStore::getEmitentCode()
{
    outBuffer o;
    o<<document.name<<document.publicKey;
    return "emitent@"+iUtils->Base64Encode(o.asString()->asString());

}
std::string blockchainData::KeyStore::getPublicAccountCode()
{
    outBuffer o;
    o<<document.name<<document.publicKey;
    return "publicAccount@"+iUtils->Base64Encode(o.asString()->asString());

}

//int32_t blockchainData::KeyStore::getPublicKeyCRC32()
//{
//    return __crc32(0,document.publicKey.data(),document.publicKey.size());
//}



outBuffer& operator<< (outBuffer& b,const blockchainData::Invoice& s)
{
    b<<s.emitentPublicKeySHA1<<s.creditorPublicKeySHA1<<s.amount<<s.comments<<s.date;
    return b;
}

inBuffer& operator>> (inBuffer& b,  blockchainData::Invoice& s)
{
    b>>s.emitentPublicKeySHA1>>s.creditorPublicKeySHA1>>s.amount>>s.comments>>s.date;
    return b;
}
outBuffer& operator<< (outBuffer& b,const blockchainData::Payment::Document& s)
{

    b<<s.emitentPublicKeySHA1<<s.debetorPublicKeySHA1<<s.date<<s.creditorPublicKeySHA1<<s.amount<<s.invoiceId;
    return b;
}
//outBuffer& operator<< (outBuffer& b,const blockchainData::PaymentCompressed::Document& s)
//{
//    b<<s.emitentPublicKeyId<<s.debetorPublicKeyId<<s.date<<s.invoiceId<<s.creditorPublicKeyId<<s.amount;
//    return b;
//}
inBuffer& operator>> (inBuffer& b,  blockchainData::Payment::Document& s)
{
    b>>s.emitentPublicKeySHA1>>s.debetorPublicKeySHA1>>s.date>>s.creditorPublicKeySHA1>>s.amount>>s.invoiceId;
    return b;

}
//inBuffer& operator>> (inBuffer& b,  blockchainData::PaymentCompressed::Document& s)
//{
//    b>>s.emitentPublicKeyId>>s.debetorPublicKeyId>>s.date>>s.invoiceId>>s.creditorPublicKeyId>>s.amount;
//    return b;

//}
outBuffer& operator<< (outBuffer& b,const blockchainData::Payment& s)
{
    b<<s.document<<s.sign_sha256_rsaByUserPrivKey;
    return b;
}
//outBuffer& operator<< (outBuffer& b,const blockchainData::PaymentCompressed& s)
//{
//    b<<s.document<<s.sign_sha256_rsaByUserPrivKey;
//    return b;
//}
inBuffer& operator>> (inBuffer& b,  blockchainData::Payment& s)
{
    b>>s.document>>s.sign_sha256_rsaByUserPrivKey;
    return b;

}
outBuffer& operator<< (outBuffer& b,const blockchainData::Registration& s)
{
    b<<s.document;
    return b;
}
inBuffer& operator>> (inBuffer& b,  blockchainData::Registration& s)
{
    b>>s.document;
    return b;

};


outBuffer& operator<< (outBuffer& b,const blockchainData::Registration::Document& s)
{
    b<<s.date<<s.pubkey;
    return b;
}
inBuffer& operator>> (inBuffer& b,  blockchainData::Registration::Document& s)
{
    b>>s.date>>s.pubkey;
    return b;

}

outBuffer& operator<< (outBuffer& b,const blockchainData::SetCreditLimit::Document& s)
{
    b<<s.credit_limit<<s.emitentPublicKeySHA1<<s.date<<s.debetorPublicKeySHA1;
    return b;
}
inBuffer& operator>> (inBuffer& b,  blockchainData::SetCreditLimit::Document& s)
{
    b>>s.credit_limit>>s.emitentPublicKeySHA1>>s.date>>s.debetorPublicKeySHA1;
    return b;

}
outBuffer& operator<< (outBuffer& b,const blockchainData::SetCreditLimit& s)
{
    b<<s.document;
    return b;
}
inBuffer& operator>> (inBuffer& b,  blockchainData::SetCreditLimit& s)
{
    b>>s.document;
    return b;

};

void blockchainData::Payment::create(const SHA1_id& emitentPublicKeySHA1,
                                     const SHA1_id& debetorPublicKeySHA1,
                                     const SHA1_id& creditorPublicKeySHA1,
                                     double amount,
                                     const std::string& invoiceId,
                                     const time_t& date,
                                     const RSA_id &privKey_decoded
                                     )
{
    I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);


    document.emitentPublicKeySHA1=emitentPublicKeySHA1;
    document.date=date;
    document.debetorPublicKeySHA1=debetorPublicKeySHA1;
    document.creditorPublicKeySHA1=creditorPublicKeySHA1;
    document.amount=amount;
    document.invoiceId=invoiceId;




    st_rsa rsa;
    rsa.initFromPrivateKey(privKey_decoded.toString());

    outBuffer o;
    o<<document;

    std::string sha256=ssl->sha256(o.asString()->asString());
    std::string sha256_rsa=rsa.privateEncrypt(sha256);
    sign_sha256_rsaByUserPrivKey=sha256_rsa;


}


void blockchainData::SetCreditLimit::create(const SHA1_id& emitentPublicKeySHA1,
                                     const SHA1_id& debetorPublicKeySHA1,
                                     double credit_limit,
                                     const int64_t &date,
                                     const RSA_id &privKey_decoded
                                     )
{
    I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);


    document.emitentPublicKeySHA1=emitentPublicKeySHA1;
    document.date=date;
    document.debetorPublicKeySHA1=debetorPublicKeySHA1;
    document.credit_limit=credit_limit;




    st_rsa rsa;
    rsa.initFromPrivateKey(privKey_decoded.toString());

    outBuffer o;
    o<<document;

    std::string sha256=ssl->sha256(o.asString()->asString());
    std::string sha256_rsa=rsa.privateEncrypt(sha256);
    sign_sha256_rsaByUserPrivKey=sha256_rsa;
}

