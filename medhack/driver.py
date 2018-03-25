import subprocess

def test(os):
    p = subprocess.Popen(['python', 'algo.py', '--action', 'prediction'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    
    osStr = ""
    if(len(os) > 0):
        osStr = os[0]
        for i in range(1,len(os)):
            osStr = osStr + "\n" + os[i]
 
    out, _ = p.communicate(osStr)
    print out
    
    
def testSymptoms():
    p = subprocess.Popen(['python', 'algo.py', '--action', 'symptoms'], stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    out, _ = p.communicate()
    print out

test(["dispnee", "durere localizare precordiala", "coma"])
test(["dispnee", "durere localizare precordiala", "aritmie", "ahc - ima", "anxietate"])
test(["dezhidratare", "dispnee", "vertij", "sincopa", "cefalee"])
test(["cmv - consum droguri", "cefalee", "greata", "febra", "hipotensiune"])
testSymptoms()