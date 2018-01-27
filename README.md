# Pigeon

**An open-source and distributed communicate system**

**中文版 请参阅同目录下“读我.md”**

##Why we need such software

The Internet is no more a free place where you can easily hide yourself. The big brother is watching you!

We urgently need a way to communicate anonymously.

With p2p technology, the message you sent doesn't need to go through someone's server, which makes it very hard to track you or block you.

Just install this software on your server, you can make contribution to our cause!



##Client Requests should be sent in the following format 

#### Over all

Client shall sent messages of 4096 Bytes.

A message shall start with an ASCII char representing the service it wants to use. For example, if you want to sign in , you should make the very Byte '1'.

Then come 3 Bytes of '\0'.

Then come contents. Bytes not in use shall all be '\0' to prevent undefined  circumstances.

The server will return the result to the same IP and port from which you sent the request.

For example , If you want to create an account. You should just sent:

'1'for the first byte, then come 3 bytes of '\0', and 32 bytes as your ID(Of course, few people use IDs as long as 32Bytes, so you can just use '\0' to make it short), then comes your finger print(the MD5_32 of your password). And the rest of 4096 bytes shall be filled with '\0'.

The server's reply also begins with the char '1' and 3 bytes of '\0' and follows a brief char[]. If the char[] is "Success!\0", It means success. Else, it will tell you where is wrong.

For undefined circumstances, it will simply return 4096 Bytes of '\0'.  Or will not reply at all if the message length is not 4096.

#### 1. Sign in

'1'for the first byte, then come 3 bytes of '\0', and 32 bytes as your ID(Of course, few people use IDs as long as 32Bytes, so you can just use '\0' to make it short), then comes your finger print(the MD5_32 of your password). And the rest of 4096 bytes shall be filled with '\0'.

The server's reply also begins with the char '1' and 3 bytes of '\0' and follows a brief char[]. If the char[] is "Success!\0", It means success. Else, it will tell you where is wrong.

#### 2.Login 

'2'for the first byte, then come 3 bytes of '\0', and 32 bytes as your ID(Of course, few people use IDs as long as 32Bytes, so you can just use '\0' to make it short), then comes your finger print(the MD5_32 of your password). And the rest of 4096 bytes shall be filled with '\0'.

The server's reply also begins with the char '2' and 3 bytes of '\0' and follows a brief char[]. If the char[] is "Success!\0", It means success. Else, it will tell you where is wrong.

#### 3.Change finger print

'3'for the first byte, then come 3 bytes of '\0', and 32 bytes as your ID(Of course, few people use IDs as long as 32Bytes, so you can just use '\0' to make it short), then comes your old finger print(the MD5_32 of your old password), then comes your new finger print(the MD5_32 of your new password). And the rest of 4096 bytes shall be filled with '\0'.

The server's reply also begins with the char '3' and 3 bytes of '\0' and follows a brief char[]. If the char[] is "Success!\0", It means success. Else, it will tell you where is wrong.

#### 4.Log out

'4'for the first byte, then come 3 bytes of '\0', and 32 bytes as your ID(Of course, few people use IDs as long as 32Bytes, so you can just use '\0' to make it short), then comes your finger print(the MD5_32 of your password). And the rest of 4096 bytes shall be filled with '\0'.

The server will not reply it.



#### 5.Get you friends' Address

'5'for the first byte, then come 3 bytes of '\0', and 32 bytes as your friends ID(Of course, few people use IDs as long as 32Bytes, so your friends may just use '\0' to make it short)

The server's reply also begins with the char '5' and 3 bytes of '\0' and follows a byte. The byte represents the status of your friend, '1' for online, '2' for offline, '3' for no such user. Then come 3 bytes of '\0'.If your friend is online, there will also be a char [] representing the address of your friend.

Be aware, it is possible that under some circumstances , the server thinks that your friend is online but actually he is not.

Also , a Client shall chache the address of your friends to make  the security of your chat higher and the pressure of the server lower.

#### 6. Erase your account

Erasing a account is meaningless.

#### 

#### 





