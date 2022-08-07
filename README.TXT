JCrypt by James McConnel (2008)

Scrambles ASCII text files using a very simple additive algorithim,
which uses a password (key) supplied by the user to do the scrambling.

It may be useful, but do not use it if you are looking for robust 
encryption.  It was simply a diversion for me.  Besides which, any security 
it might provide falls apart if the password is even partially compromised,
for instance: if your password is "pass" and the file is "decrypted" using the
word "bass" 3/4 of the characters in the file will be shown correctly.  It 
really isn't all that bad, I suppose.  To get much you would have to correctly guess
both the length of the password, and most of the characters in it.

Send comments to: yehoodig@gmail.com 

Written in CPP.