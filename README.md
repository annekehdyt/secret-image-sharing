# secret-image-sharing
This program based on the 1979 Shamir's secret sharing, and secret image sharing by CC Thien
http://www.sciencedirect.com/science/article/pii/S0097849302001310

Instead of one bit of secret message, we applied images and treat its pixels as bunch of secret message. Then, we calculate each of the pixel as coefficients of polynomial. Here, we wanted to share the image-keys with a group of n participants. The condition is that it is possible to decrypt the message with only t participants, where 1<=t<=n.  In this program, we modified the computation under finite field -> Galois Field (2^8), instead of standard arithmetic calculation.

Please refer to the file for the code :

GFfuntion.cpp
SScoefficient.cpp
distribution.cpp
