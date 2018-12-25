# RSALicenseModule
this Module is used to encrypt license file and decrypt license file via RSA algrithm

There are 3 projects in CMakeFileList.txt.
### 1. RSALicenseLib:
  this project is the core functionality to provide RSA encryption and decryption. 
  
### 2. RSALicenseMaker:
  this project is the example which demonstrate how to use RSALicenseLib to encrypt 
  one plaintext document specified by the second argument of this program, and finally 
  write the encrypted text into ok.lic
  You can see that only N, D is stored in this program
  
### 3. RSADecoder:
  this project is the example which demonstrate how to use RSALicenseLib to decrypt
  a RSAed license file specified by the second argument of this program and finally 
  write the decrypted text into ok.txt
  You can see that only N, E is stored in this program
  
### Note: 
be carefully to store your private key [N, D] so that you can make your license 
be in safe state.
