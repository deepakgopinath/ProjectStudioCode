import os

count=0;
for dirpath, dirname, filenames in os.walk('.'):
    for filename in filenames:
        ext= filename.split('.')[-1]
        if(ext =='jpg'):
            os.rename(filename, str(count)+ ".jpg")
            count= count+1
    
