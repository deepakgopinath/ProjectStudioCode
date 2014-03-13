import os

for dirpath, dirname, filenames in os.walk('.'):
    for filename in filenames:
        ext= filename.split('.')[-1]
        if(ext=='mp4'):
            print "hello"
            outputPath=filename.rsplit('.',1)[0]
            if not os.path.exists(outputPath+"_edge"):
                os.mkdir(outputPath+"_edge")
            command= 'ffmpeg -i \"'+ filename+ '\" -vf edgedetect=low=0.01:high=0.06,colorchannelmixer=.8:.8:.8:0:.8:.4:.8:0:.8:.4:.8 -s  320x180  \"'+ outputPath+ "_edge/"+ "%d.bmp\""
            print command
            os.system(command)
            if not os.path.exists(outputPath):
                os.mkdir(outputPath)
            command= 'ffmpeg -i \"'+ filename+ '\"   -s  320x180 \"'+ outputPath+ '/'+ "%d.bmp\""
            print command
            os.system(command)
