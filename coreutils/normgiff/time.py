import matplotlib.pyplot as plt
import numpy
file = open('times_lin.txt', 'r')

num_array = []
average = []
for line in file:
    num_array.append(float(line))
z = numpy.polyfit(range(0,len(num_array)), num_array,1)
p = numpy.poly1d(z)
x = range(0,len(num_array))
plt.plot(x,num_array,'ro', label="Time Plots")
plt.plot(x, p(x),'r-', label="Trendline")
#plots_legend = plt.legend(handles=[plots], loc=0)
#ax = plt.gca().add_artist(plots_legend)
plt.legend(loc=0)
plt.ylabel("Execution Time in Seconds")
plt.xlabel("The Square Root of Number of Characters  in Converted String")
plt.title("Figure 1: Plot of Execution Time vs. Number of Characters ")
plt.show()
