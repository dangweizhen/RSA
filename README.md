# RSA

RSA encryption algorithm

bigInt.h  bigInt.cpp：大数运算库

gcd.h：最大公因子及模逆算法实现

mrTest.h：Miller-Rabin检测的实现

power.h：模幂运算的实现

random.h：随机整数的生成库

main.cpp：测试程序，输入一个字符串，生成一对秘钥并保存（公钥名为pubkey.txt，私钥名为prikey.txt），用这对秘钥对字符串进行加密和解密

keygen.cpp:生成秘钥对，无需输入，输出秘钥对保存为文件（公钥名为pubkey.txt，私钥名为prikey.txt）

encryption.cpp:加密程序，输入明文，输出密文

decryption.cpp：解密程序，输入密文，输出明文

