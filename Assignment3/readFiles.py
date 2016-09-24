# import os

listFiles = [filename for filename in os.listdir('/home/jpainumkal/Downloads/cplus/src/d1_c1/') if filename.startswith("outfile_")]
print listFiles

sumofFitness=0
opfile = open('d3_cm3.txt', 'w')

for gen in range(0,50):
    opfile.write(str(gen)+"\t")
    for fit_val in range (1,4):
        for file in listFiles:
            lines = open('/home/jpainumkal/Downloads/cplus/src/d3_c3/'+file,'r').readlines()
            values=lines[gen].split('\t')
          
            sumofFitness=sumofFitness+float(values[fit_val])

        sumofFitness=sumofFitness/len(listFiles)
        opfile.write(str(sumofFitness)+"\t\t")
        sumofFitness=0
    opfile.write("\n")



#plotting the graph
import matplotlib.pyplot as plt
x =[]
y=[]
file = 'd4_cm3.txt'
lines = open('/home/jpainumkal/Downloads/cplus/src/'+file,'r').readlines()

for gen in range(0,50):
    values=lines[gen].split('\t')
    x.append(float(values[0]))
    y.append(float(values[1]))

print x
print y

plt.plot(x,y)
plt.xlabel('Generations')
plt.ylabel('Fitness')
plt.title('Average of the Minimum in the Population  \n( Crossover Probability (0.99) and Mutation Probability (0.01))')
plt.show()


