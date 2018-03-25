# Hello World program in Python
    
diseaseObservationList = [
  
("ima","sugar",0.0217391304347826),
("ima","copil",0.0217391304347826),
("ima","adolescent",0.0217391304347826),
("ima","adult",0.0217391304347826),
("ima","varstnic",0.0217391304347826),
("ima","mascul",0.0217391304347826),
("ima","ahc - ima",0.0217391304347826),
("ima","app - ima",0.0217391304347826),
("ima","app - arterite",0.0217391304347826),
("ima","app - cardiopatii valvulare",0.0217391304347826),
("ima","app - dz",0.0217391304347826),
("ima","app - anemie",0.0217391304347826),
("ima","app - boli endocrine",0.0217391304347826),
("ima","app - tulburari de ritm",0.0217391304347826),
("ima","app - tulburari de conducere",0.0217391304347826),
("ima","app - obezitate",0.0217391304347826),
("ima","app - hta",0.0217391304347826),
("ima","cmv - fumat",0.0217391304347826),
("ima","cmv - sedentarism",0.0217391304347826),
("ima","cmv - consum droguri",0.0217391304347826),
("ima","cmv - stres",0.0217391304347826),
("ima","debut simptomalogie - acut",0.0217391304347826),
("ima","durere localizare toracica",0.0217391304347826),
("ima","durere localizare precordiala",0.0217391304347826),
("ima","durere localizare epigastrica",0.0217391304347826),
("ima","iradiere durere",0.0217391304347826),
("ima","durere caracter presiune",0.0217391304347826),
("ima","durere caracter arsura",0.0217391304347826),
("ima","durere durata - peste 20 min",0.0217391304347826),
("ima","dispnee",0.0217391304347826),
("ima","transpiratii",0.0217391304347826),
("ima","greata",0.0217391304347826),
("ima","varsaturi",0.0217391304347826),
("ima","anxietate",0.0217391304347826),
("ima","ameteli",0.0217391304347826),
("ima","fatigabilitate",0.0217391304347826),
("ima","sincopa",0.0217391304347826),
("ima","simptome pseudogripale",0.0217391304347826),
("ima","palpitatii",0.0217391304347826),
("ima","tahicardie",0.0217391304347826),
("ima","bradicardie",0.0217391304347826),
("ima","aritmie",0.0217391304347826),
("ima","hipertensiune",0.0217391304347826),
("ima","hipotensiune",0.0217391304347826),
("ima","tahipnee",0.0217391304347826),
("ima","febra",0.0217391304347826),
("avc","sugar",0.0227272727272727),
("avc","copil",0.0227272727272727),
("avc","adolescent",0.0227272727272727),
("avc","adult",0.0227272727272727),
("avc","varstnic",0.0227272727272727),
("avc","mascul",0.0227272727272727),
("avc","debut - brusc",0.0227272727272727),
("avc","ahc - avc",0.0227272727272727),
("avc","app - avc",0.0227272727272727),
("avc","app - hta",0.0227272727272727),
("avc","app - icc",0.0227272727272727),
("avc","app - ima",0.0227272727272727),
("avc","app - dz",0.0227272727272727),
("avc","app - obezitate",0.0227272727272727),
("avc","cmv - sedentarism",0.0227272727272727),
("avc","cmv - fumat",0.0227272727272727),
("avc","paralizie membru superior",0.0227272727272727),
("avc","paralizie membru inferior",0.0227272727272727),
("avc","paralizie faciala",0.0227272727272727),
("avc","pareza membru superior",0.0227272727272727),
("avc","pareza membru inferior",0.0227272727272727),
("avc","pareza faciala",0.0227272727272727),
("avc","tulburari de vorbire",0.0227272727272727),
("avc","diplopie ",0.0227272727272727),
("avc","vedere incetosata",0.0227272727272727),
("avc","tulburari de coordonare",0.0227272727272727),
("avc","tulburari de echilibru",0.0227272727272727),
("avc","cefalee",0.0227272727272727),
("avc","parestezii membru superior",0.0227272727272727),
("avc","parestezii membru inferior",0.0227272727272727),
("avc","parestezii faciale",0.0227272727272727),
("avc","tulburari de mers ",0.0227272727272727),
("avc","fatigabilitate",0.0227272727272727),
("avc","ameteli",0.0227272727272727),
("avc","vertij",0.0227272727272727),
("avc","sincopa",0.0227272727272727),
("avc","greata ",0.0227272727272727),
("avc","varsaturi",0.0227272727272727),
("avc","dificultati la inghitire",0.0227272727272727),
("avc","convulsii",0.0227272727272727),
("avc","alterarea starii de constienta",0.0227272727272727),
("avc","fotofobie",0.0227272727272727),
("avc","amauroza",0.0227272727272727),
("avc","coma",0.0227272727272727),
("ira","sugar",0.0256410256410256),
("ira","copil",0.0256410256410256),
("ira","adolescent",0.0256410256410256),
("ira","adult",0.0256410256410256),
("ira","varstnic",0.0256410256410256),
("ira","mascul",0.0256410256410256),
("ira","debut simptomalogie - acut",0.0256410256410256),
("ira","app - glomerulonefrita",0.0256410256410256),
("ira","app - lupus",0.0256410256410256),
("ira","app - vasculita",0.0256410256410256),
("ira","app - mielom multiplu",0.0256410256410256),
("ira","app - sclerodermie",0.0256410256410256),
("ira","app - cancer vezica urinara",0.0256410256410256),
("ira","app - hiperplazie prostata",0.0256410256410256),
("ira","app - litiaza renala",0.0256410256410256),
("ira","app - boala arteriala periferica",0.0256410256410256),
("ira","app - dz",0.0256410256410256),
("ira","app - hta",0.0256410256410256),
("ira","app - afectiuni renale",0.0256410256410256),
("ira","app - consum hipotensoare",0.0256410256410256),
("ira","app - consum aspirina/ains",0.0256410256410256),
("ira","app - insuficienta hepatica",0.0256410256410256),
("ira","cmv - consum alcool",0.0256410256410256),
("ira","cmv - consum droguri",0.0256410256410256),
("ira","cmv - metale grele",0.0256410256410256),
("ira","anafilaxie",0.0256410256410256),
("ira","arsuri ",0.0256410256410256),
("ira","dezhidratare",0.0256410256410256),
("ira","ima",0.0256410256410256),
("ira","infectie",0.0256410256410256),
("ira","edeme membre inferioare",0.0256410256410256),
("ira","dispnee",0.0256410256410256),
("ira","durere localizare toracica",0.0256410256410256),
("ira","fatigabilitate",0.0256410256410256),
("ira","alterarea starii de constienta",0.0256410256410256),
("ira","greata",0.0256410256410256),
("ira","convulsii",0.0256410256410256),
("ira","coma",0.0256410256410256),
("ira","durere caracter constrictiv",0.0256410256410256),
("apa","sugar",0.05),
("apa","copil",0.05),
("apa","adolescent",0.05),
("apa","adult",0.05),
("apa","varstnic",0.05),
("apa","mascul",0.05),
("apa","app - helmintoza",0.05),
("apa","app - consum steroizi",0.05),
("apa","app - dz",0.05),
("apa","durere localizare abdominala",0.05),
("apa","durere difuza",0.05),
("apa","durere localizata fid",0.05),
("apa","greata",0.05),
("apa","varsaturi",0.05),
("apa","distensie abdominala",0.05),
("apa","febra",0.05),
("apa","subfebrilitati",0.05),
("apa","constipatie",0.05),
("apa","diaree",0.05),
("apa","inapetenta",0.05),

]
    
diseaseGravityList = [
    ("ima",	    9,          0.03846153846),
    ("avc",	    8,         0.3846153846),
    ("ira",	    7,         0.3846153846),
    ("apa",	    5,         0.1923076923)
]
    
eps = 1e-10
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
    obsCountDict = dict()
    for (d,o,p) in dol:
        obsSet.add(o)
        if not d in obsCountDict:
            obsCountDict[d] = 0
            
        obsCountDict[d] = obsCountDict[d] + 1
        
    obsCount = len(obsSet)
    table = dict()

    for (d,o,p) in dol:
        assert( 0.0 <= p and p <= 1.0 )
        assert(obsCount >= obsCountDict[d])
        k = (d,o)
        debug(str(k))
        assert(not k in table)
        table[k] = p / ( 1.0 + (obsCount - obsCountDict[d]) * eps )

    return (table, obsSet)

# returns the probability of an observation given a disease
# using the observation given disease table
def getObservationGivenDiseaseProbability(og,observation,disease):
    k = (disease,observation)
    if k in og:
        p = og[k]
        assert( 0.0 <= p and p <= 1.0 )
        return p
        
    return eps
    
# returns the probability of an observation given not a disease
# using the observation given disease table and disease gravity list
def getObservationGivenNotDiseaseProbability(og,dgl,observation,disease):
    totalObservation = 0
    totalNotDisease = getNotDiseaseProbability(dgl,disease)
    
    for (d,g,p) in dgl:
        if (d != disease):
            p = getObservationGivenDiseaseProbability(og,observation,d)
            assert(p >= eps)
            totalObservation = totalObservation + p * getDiseaseProbability(dgl, d)
            assert(totalObservation > 0)

    result = totalObservation / totalNotDisease
    assert(0.0 <= result and result <= 1.0)
    return result
    
# checks the database for inconsistencies. Uses both
# disease observation list and disease gravity list
def checkDatabase(dol, dgl):
    diseaseSymptomProbabilityDict = dict()
    for (d,o,p) in dol:
        if d in diseaseSymptomProbabilityDict:
            diseaseSymptomProbabilityDict[d] = diseaseSymptomProbabilityDict[d] + p
        else:
            diseaseSymptomProbabilityDict[d] = p
    
    totalDiseaseProbability = 0.0
            
    for (d,g,p) in dgl:
        totalDiseaseProbability = totalDiseaseProbability + p
        debug("d=" + d)
        debug("p=" + str(p))
        assert(isClose(diseaseSymptomProbabilityDict[d],1.0))
        
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
        assert(observation in obsSet)
        debug("observation=" + observation)
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
    print os
    print getPredictionList(diseaseObservationList, diseaseGravityList, os)
    
    
test(["dispnee", "durere localizare precordiala", "coma"])
test(["dispnee", "durere localizare precordiala", "aritmie"])
test(["dezhidratare", "dispnee", "vertij", "sincopa", "cefalee"])
test(["cmv - consum droguri", "cefalee", "greata", "febra", "hipotensiune"])