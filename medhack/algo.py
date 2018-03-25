import argparse
import sys

diseaseObservationList = [
  
("ima","barbat",0.5),
("ima","ahc - ima",0.75),
("ima","app - ima",0.75),
("ima","app - arterite",0.75),
("ima","app - cardiopatii valvulare",0.75),
("ima","app - dz",0.75),
("ima","app - anemie",0.75),
("ima","app - boli endocrine",0.75),
("ima","app - tulburari de ritm",0.75),
("ima","app - tulburari de conducere",0.75),
("ima","app - obezitate",0.75),
("ima","app - hta",0.75),
("ima","cmv - fumat",0.75),
("ima","cmv - sedentarism",0.75),
("ima","cmv - consum droguri",0.75),
("ima","cmv - stres",0.75),
("ima","durere localizare retrosternala",0.75),
("ima","debut simptomalogie - acut",0.75),
("ima","durere localizare toracica",0.75),
("ima","durere localizare precordiala",0.75),
("ima","durere localizare epigastrica",0.75),
("ima","iradiere durere",0.75),
("ima","durere caracter presiune",0.75),
("ima","durere caracter arsura",0.75),
("ima","durere durata - peste 20 min",0.75),
("ima","dispnee",0.75),
("ima","transpiratii",0.75),
("ima","greata",0.75),
("ima","varsaturi",0.75),
("ima","anxietate",0.75),
("ima","ameteli",0.75),
("ima","fatigabilitate",0.75),
("ima","sincopa",0.75),
("ima","simptome pseudogripale",0.75),
("ima","palpitatii",0.75),
("ima","tahicardie",0.75),
("ima","bradicardie",0.75),
("ima","aritmie",0.75),
("ima","hipertensiune",0.75),
("ima","hipotensiune",0.75),
("ima","tahipnee",0.75),
("ima","febra",0.75),
("avc","barbat",0.5),
("avc","debut - brusc",0.75),
("avc","ahc - avc",0.75),
("avc","app - avc",0.75),
("avc","app - hta",0.75),
("avc","app - icc",0.75),
("avc","app - ima",0.75),
("avc","app - dz",0.75),
("avc","app - obezitate",0.75),
("avc","cmv - sedentarism",0.75),
("avc","cmv - fumat",0.75),
("avc","paralizie membru superior",0.75),
("avc","paralizie membru inferior",0.75),
("avc","paralizie faciala",0.75),
("avc","pareza membru superior",0.75),
("avc","pareza membru inferior",0.75),
("avc","pareza faciala",0.75),
("avc","tulburari de vorbire",0.75),
("avc","diplopie",0.75),
("avc","vedere incetosata",0.75),
("avc","tulburari de coordonare",0.75),
("avc","tulburari de echilibru",0.75),
("avc","cefalee",0.75),
("avc","parestezii membru superior",0.75),
("avc","parestezii membru inferior",0.75),
("avc","parestezii faciale",0.75),
("avc","tulburari de mers",0.75),
("avc","fatigabilitate",0.75),
("avc","ameteli",0.75),
("avc","vertij",0.75),
("avc","sincopa",0.75),
("avc","greata",0.75),
("avc","varsaturi",0.75),
("avc","dificultati la inghitire",0.75),
("avc","convulsii",0.75),
("avc","alterarea starii de constienta",0.75),
("avc","fotofobie",0.75),
("avc","amauroza",0.75),
("avc","coma",0.75),
("ira","barbat",0.5),
("ira","debut simptomalogie - acut",0.75),
("ira","app - glomerulonefrita",0.75),
("ira","app - lupus",0.75),
("ira","app - vasculita",0.75),
("ira","app - mielom multiplu",0.75),
("ira","app - sclerodermie",0.75),
("ira","app - cancer vezica urinara",0.75),
("ira","app - hiperplazie prostata",0.75),
("ira","app - litiaza renala",0.75),
("ira","app - boala arteriala periferica",0.75),
("ira","app - dz",0.75),
("ira","app - hta",0.75),
("ira","app - afectiuni renale",0.75),
("ira","app - consum hipotensoare",0.75),
("ira","app - consum aspirina/ains",0.75),
("ira","app - insuficienta hepatica",0.75),
("ira","cmv - consum alcool",0.75),
("ira","cmv - consum droguri",0.75),
("ira","cmv - metale grele",0.75),
("ira","anafilaxie",0.75),
("ira","arsuri",0.75),
("ira","dezhidratare",0.75),
("ira","ima",0.75),
("ira","infectie",0.75),
("ira","edeme membre inferioare",0.75),
("ira","dispnee",0.75),
("ira","durere localizare toracica",0.75),
("ira","fatigabilitate",0.75),
("ira","alterarea starii de constienta",0.75),
("ira","greata",0.75),
("ira","convulsii",0.75),
("ira","coma",0.75),
("ira","durere caracter constrictiv",0.75),
("apa","barbat",0.5),
("apa","app - helmintoza",0.75),
("apa","app - consum steroizi",0.75),
("apa","app - dz",0.75),
("apa","durere localizare abdominala",0.75),
("apa","durere difuza",0.75),
("apa","durere localizata fid",0.75),
("apa","greata",0.75),
("apa","varsaturi",0.75),
("apa","distensie abdominala",0.75),
("apa","febra",0.75),
("apa","subfebrilitati",0.75),
("apa","constipatie",0.75),
("apa","diaree",0.75),
("apa","inapetenta",0.75),
("cdz","barbat",0.5),
("cdz","ahc - boli autoimune",0.75),
("cdz","ahc - dz",0.75),
("cdz","app - consum droguri",0.75),
("cdz","app - consum alcool",0.75),
("cdz","app - ima",0.75),
("cdz","app - pierdere in greutate",0.75),
("cdz","app - infectie",0.75),
("cdz","app - dz",0.75),
("cdz","nerespectare tratament dz",0.75),
("cdz","polidipsie",0.75),
("cdz","poliurie",0.75),
("cdz","fatigabilitate",0.75),
("cdz","greata",0.75),
("cdz","varsaturi",0.75),
("cdz","dureri abdominale abdominala",0.75),
("cdz","dureri difuze",0.75),
("cdz","transpiratie",0.75),
("cdz","modificarea starii de constienta",0.75),
("cdz","febra",0.75),
("cdz","frison",0.75),
("cdz","durere localizare toracica",0.75),
("cdz","dispnee",0.75),
("cdz","tahipnee",0.75),
("cdz","hipotensiune",0.75),
("cdz","tahicardie",0.75),
("cdz","halena cetonica",0.75),
("cdz","scaderea reflexelor",0.75),
("cdz","respiratie Kussmaul",0.75),
("tep","barbat",0.5),
("tep","debut simptomalogie - acut",0.75),
("tep","app - consum droguri",0.75),
("tep","app - anemie hemolitica",0.75),
("tep","app - tromboza venoasa profunda",0.75),
("tep","app - dislipidemie",0.75),
("tep","app - edeme",0.75),
("tep","dispnee",0.75),
("tep","convulsii",0.75),
("tep","sincopa",0.75),
("tep","durere abdominala",0.75),
("tep","febra",0.75),
("tep","tuse",0.75),
("tep","wheezing",0.75),
("tep","tahipnee",0.75),
("tep","raluri crepitante",0.75),
("tep","accentuarea zgomotului II",0.75),
("tep","tahicardie",0.75),
("tep","galop III sau IV",0.75),
("tep","tromboflebita",0.75),
("tep","edeme membre inferioare",0.75),
("tep","cianoza",0.75),
("tep","durere toracica",0.75),
("tep","durere severa",0.75),
("tep","hemoptizie",0.75),
("tep","anxietate",0.75),
("tep","transpiratii",0.75),
("tep","palpitatii",0.75),
("tep","ameteli",0.75),
("ars I","arsura grad I",0.75),
("ars I","leziune eritematoasa",0.75),
("ars I","absenta flictenelor",0.75),
("ars I","durere",0.75),
("ars II","arsura grad II",0.75),
("ars II","durere",0.75),
("ars II","leziune eritematoasa",0.75),
("ars II","flictene",0.75),
("ars III","arsura grad III",0.75),
("ars III","durere atenuata",0.75),
("ars III","leziune alba / neagra",0.75),
("ars IV","arsura grad IV",0.75),
("ars IV","leziune tegumentara",0.75),
("ars IV","interesarea muschilor, fasciilor, oase, alte structuri",0.75),
("Fractura distala radius","barbat",0.5),
("Fractura distala radius","app - osteoporoza",0.75),
("Fractura distala radius","app - sedentarism",0.75),
("Fractura distala radius","app - hipocalcemie",0.75),
("Fractura distala radius","app - tumori osoase",0.75),
("Fractura distala radius","deformare in dos de furculita radius",0.75),
("Fractura distala radius","scurtarea membrului superior",0.75),
("Fractura distala radius","pierderea mobilitatii membrului'",0.75),
("Fractura distala radius","tumefactie",0.75),
("Fractura distala radius","durere",0.75),
("Fractura distala radius","crepitatii osoase",0.75),
("Fractura col femural","barbat",0.5),
("Fractura col femural","app - osteoporoza",0.75),
("Fractura col femural","app - sedentarism",0.75),
("Fractura col femural","app - hipocalcemie",0.75),
("Fractura col femural","app - tumori osoase",0.75),
("Fractura col femural","rotatie externa si adductie membru inferior",0.75),
("Fractura col femural","scurtarea membrului inferior",0.75),
("Fractura col femural","pierderea mobilitatii membrului'",0.75),
("Fractura col femural","tumefactie",0.75),
("Fractura col femural","durere",0.75),
("Fractura col femural","crepitatii osoase",0.75),
("Intoxicatie co","cmv - risc intoxicatie cu co",0.75),
("Intoxicatie co","cefalee",0.75),
("Intoxicatie co","fatigabilitate",0.75),
("Intoxicatie co","greturi",0.75),
("Intoxicatie co","varsaturi",0.75),
("Intoxicatie co","alterarea starii de constienta",0.75),
("Intoxicatie co","ameteli",0.75),
("Intoxicatie co","dispnee",0.75),
("litiaza renala","barbat",0.5),
("litiaza renala","ahc - litiaza renala",0.75),
("litiaza renala","app - litiaza renala",0.75),
("litiaza renala","app - insuficienta renala",0.75),
("litiaza renala","app - infectii urinare",0.75),
("litiaza renala","dezhidratare",0.75),


]
    
diseaseGravityList = [
    ("ima",9,   0.0353982300884956),
    ("avc",8,   0.353982300884956),
    ("ira",7,   0.353982300884956),
    ("apa",5,   0.176991150442478),
    ("cdz",6,   0.0707964601769911),
    ("tep",10,  0.00884955752212389),

]

debugIsOn = False

def debug(str):
    if debugIsOn:
        print(str)
    
# checks two float points to be relativiley close to each other
def isClose(l,r,e=1e-8):
    return abs(l-r) <= e * max(abs(l), abs(r))

# returns unique list of diseases from the disease gravity list
def getDiseaseList(dgl):
    l = []
    for (d,o,p) in dgl:
        l.append(d)
    return l
   
# returns the probability of a disease using the disease
# gravity list
def getDiseaseProbability(dgl,disease):
    for (d,g,p) in dgl:
        assert(0.0 <= p and p <= 1.0)
        if d == disease:
            return p
    assert(False)
    
    
# returns the probability of not having the disease using the
# disease gravity list
def getNotDiseaseProbability(dgl,disease):
    p = getDiseaseProbability(dgl, disease)
    assert(0.0 <= p and p <= 1.0 )
    return 1.0 - p
   
 
# computes the observation given disease probability table
# and observation set using the disease observation list
def computeObservationGivenDiseaseTable(dol):
    obsSet = set()
    for (d,o,p) in dol:
        obsSet.add(o)
       
    table = dict()

    for (d,o,p) in dol:
        assert( 0.0 <= p and p <= 1.0 )
        k = (d,o)
        debug(str(k))
        assert(not k in table)
        table[k] = p

    return (table, obsSet)

# returns the probability of an observation given a disease
# using the observation given disease table
def getObservationGivenDiseaseProbability(og,observation,disease):
    k = (disease,observation)
    if k in og:
        p = og[k]
        assert( 0.0 <= p and p <= 1.0 )
        return p
        
    return 0.5
    
# returns the probability of an observation given not a disease
# using the observation given disease table and disease gravity list
def getObservationGivenNotDiseaseProbability(og,dgl,observation,disease):
    totalObservation = 0
    totalNotDisease = getNotDiseaseProbability(dgl,disease)
    
    for (d,g,p) in dgl:
        if (d != disease):
            p = getObservationGivenDiseaseProbability(og,observation,d)
            totalObservation = totalObservation + p * getDiseaseProbability(dgl, d)
            assert(totalObservation > 0)

    result = totalObservation / totalNotDisease
    assert(0.0 <= result and result <= 1.0)
    return result
    
# checks the database for inconsistencies. Uses both
# disease observation list and disease gravity list
def checkDatabase(dol, dgl):
    diseaseObservationSet = set()
    for (d,o,p) in dol:
        assert(0.0 <= p and p <= 1.0)
        debug("disease=" + d)
        debug("observation=" + o)
        k = (d,o)
        assert(not k in diseaseObservationSet)
        diseaseObservationSet.add(k)
    
    totalDiseaseProbability = 0.0
            
    for (d,g,p) in dgl:
        totalDiseaseProbability = totalDiseaseProbability + p
        
    assert(isClose(totalDiseaseProbability, 1.0))
    

# returns the probability of a disease given an observation set
# using observation given disease table, observationSet and disease gravity list
def getDiseaseGivenObservationProbability(og,obsSet,dgl,disease,os):
    p = getDiseaseProbability(dgl,disease)
    n = getNotDiseaseProbability(dgl,disease)
    debug("disease=" + disease)
    debug("p=" + str(p))
    debug("n=" + str(n))
    for observation in os:
        debug("observation=" + observation)
        assert(observation in obsSet)
        p = p * getObservationGivenDiseaseProbability(og, observation, disease)
        n = n * getObservationGivenNotDiseaseProbability(og, dgl, observation, disease)
        debug("p=" + str(p))
        debug("n=" + str(n))
        
    if ( p + n == 0.0 ):
        return 0.0
    
    assert( 0.0 <= p and p <= 1.0 )
    assert( 0.0 <= n and n <= 1.0 )
    result = p / ( p + n )
    
    return result
    


# returns list of (disease,probability,score) given the
# observation set as a list of observations using
# disease observation list and disease gravity list
def getPredictionList(dol,dgl,os):
    checkDatabase(dol,dgl)
    (og, obsSet) = computeObservationGivenDiseaseTable(dol)
    result = []
    for (disease,g,p) in dgl:
        diseaseProbability = getDiseaseGivenObservationProbability(og,obsSet,dgl,disease,os)
        score = diseaseProbability * g
        result.append((disease,diseaseProbability,score))
    return result
    
    
def test(os):
    osStr = ""
    for observation in os:
        osStr = osStr + "    " + observation
    for (d,p,s) in getPredictionList(diseaseObservationList, diseaseGravityList, os):
        print osStr + " ---> " + d + "     " + str(p) + "      " + str(s)
    
parser = argparse.ArgumentParser()
parser.add_argument("--action", choices=['test','prediction','symptoms'], help="The action to take", required=True )
parser.add_argument("--debug", default=False, help="Enable debug message logging", action='store_const', const=True, required=False)

args = parser.parse_args()

debugIsOn = args.debug
    
if args.action == 'test':
    test(["dispnee", "durere localizare precordiala", "coma"])
    test(["dispnee", "durere localizare precordiala", "aritmie", "ahc - ima", "anxietate"])
    test(["dezhidratare", "dispnee", "vertij", "sincopa", "cefalee"])
    test(["cmv - consum droguri", "cefalee", "greata", "febra", "hipotensiune"])
elif args.action == 'prediction':
    os = []
    for line in sys.stdin:
        os.append(line.rstrip())
    assert(len(os) > 0)
    for (d,p,s) in getPredictionList(diseaseObservationList, diseaseGravityList, os):
        print d + ";" + str(p) + ";" + str(s)
elif args.action == 'symptoms':
    (_, obsSet) = computeObservationGivenDiseaseTable(diseaseObservationList)
    for observation in obsSet:
        print observation
else:
    assert(False)
