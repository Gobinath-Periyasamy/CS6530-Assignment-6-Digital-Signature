# CS6530-Assignment-6-Digital-Signature
Assignment 6 Digital Signature

Assignments for IIT CS6530 Cryptography Basics

**Name : Gobinath Periyasamy**

**Roll Number : CS21M501**

**Registered Mail id : janu.gobi@gmail.com**

Steps to Execute the Program:

1.  To open the ecc.exe file.
2.  To input a value. Eg : 4
3.  To input b value. Eg : 5
4.  To input message x point Eg : 34
5.  To input message y point Eg : 78

Then Original message is decrypted correctly by BOB (receiver) but wrongly by EVE(attacker)


E:\IIT CS Prep\IIT Sem\Cryptography Basics\DSA\DigitalSignature>g++ -o dss.exe dss.cpp

E:\IIT CS Prep\IIT Sem\Cryptography Basics\DSA\DigitalSignature>dss.exe

Please enter a value : 4

Please enter b value : 5

The elliptic curve: y^2 mod 263 = (x^3+4x+5) mod 263



===================================================

P       : (5, 26)

Q       : (5, 237)

R       : (85, 75)

G       : (3, 71)

order of G : 59

Alice' public key Pa = 1*(3, 71) = (3, 71)

Bob's public key = (131, 93)

===================================================

Eve's public key Pj = 51*(3, 71) = (48, 131)

Please enter the message points:

message_x co-ordinate : 34

message_y co-ordinate : 78

*************************************************
* Alice's input message points : (34, 78)
*************************************************

Encrypted message points using diffie hellman :
         (cipher_x,cipher_y) = ( 246, 153 )


************************************************************
* Bob's Decrypted message points = (34, 78)
************************************************************


Eve's decrypted message from Alice = (38, 220)


--------**Eve cannot manipulate the message inbetween as Eve gets wrong message**--------

Press any key to continue . . .

