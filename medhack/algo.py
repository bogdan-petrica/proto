import argparse
import sys

from db import *

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
