@ECHO OFF
IF "%1"=="" GOTO Error
   del data.bin
   copy data%1.bin data.bin
   GOTO End
:Error
   ECHO Invalid argument
   ECHO Usage: swap number
:End