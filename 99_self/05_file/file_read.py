def fileWrite():
    fp =open("test.txt", "w")
    fp.write( "abc\ndef\nghi")
    fp.write("hello")
    fp.close()

def fileRead():
    fp =open("test.txt", "r")
    for r in ( fp.readlines() ):
        print( r )
    fp.close()

fileWrite()
fileRead()