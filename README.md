# CS6530-Assignment-6-Digital-Signature
Assignment 6 Digital Signature

Assignments for IIT CS6530 Cryptography Basics

**Name : Gobinath Periyasamy**

**Roll Number : CS21M501**

**Registered Mail id : janu.gobi@gmail.com**

Steps to Execute the Program:

1.  To open the dsaa.exe file.
2.  To input the Signatures S1 and S2 (will be dsiaplyed int the screen)
3.  To give Y or y to continue verfiication with other signature pair.


E:\IIT CS Prep\IIT Sem\Cryptography Basics\final>g++ -o dsa.exe dsa.c

E:\IIT CS Prep\IIT Sem\Cryptography Basics\final>dsa.exe

*******************************************************************************************************

**********************************

* Digital Signature Verification *

**********************************

Name    : GOBINATH

Roll No : CS21M501

*******************************************************************************************************

Private key Xa is : 25254

Public key q : 99103, a : 3, Ya : 65839, Hash Message hm : 98379

s1 : 40998

s2 : 93537

Please Enter the Signatures (Printed above)

        Enter the s1 : 40998
        Enter the s2 : 93537

V1 : 44175

v2 : 44175

*******************************************************************************************************

*  V1 and V2 for given signatures are MATCHing. Message sent by the correct Sender

*******************************************************************************************************

Want to verify for other Signatures ?

(Please give your input as (Y or y)) : y

user_input : y

Please Enter the Signatures (Printed above)

        Enter the s1 : 35462
        
        Enter the s2 : 23412

V1 : 44175

v2 : 29577

*******************************************************************************************************

*  V1 and V2 for given signatures are NOT matching, Message NOT sent by  the correct Sender

*******************************************************************************************************

Want to verify for other Signatures ?

(Please give your input as (Y or y)) : n

user_input : n

Press any key to continue . . .

E:\IIT CS Prep\IIT Sem\Cryptography Basics\final>
