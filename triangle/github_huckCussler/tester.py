#!/usr/bin/python
#
# Tony Tuttle
# Aug 28, 2015

# not tested:
#   ~ user enters < 6 args
#   ~ user enters at least 6 args but one of the first 6 is not an integer
#   ~ user enters at least 6 args the first 6 of which are integers,
#     but at least one of them is not -(2^30-1) <= arg <= 2^30-1
# all of these cases were tested by hand
import os
import subprocess

t = "./triangle"
er = "error\n"
nat = "not a triangle\n"
s = "scalene "
i = "isosceles "
a = "acute\n"
o = "obtuse\n"
r = "right\n"

in_outs = [([t], er),                                         #START error
           ([t, "1", "2", "3", "4", "5"], er),
           ([t, "b", "1", "2", "3", "4", "5"], er),
           ([t, "1", "b", "3", "4", "5", "6"], er),
           ([t, "1", "2", "-1073741824", "4", "5", "6"], er),
           ([t, "1", "2", "3", "1073741824", "5", "6"], er),  #END error
           ([t, "1", "1", "2", "1", "3", "1"], nat),          #START not a triangle
           ([t, "1", "1", "1", "4", "1", "6"], nat),          #END not a triangle
           ([t, "1", "1", "2", "5", "4", "1"], s+a),          #START easy triangles
           ([t, "1", "1", "2", "5", "0", "3"], s+o),
           ([t, "1", "1", "1", "3", "4", "1"], s+r),
           ([t, "1", "1", "3", "9", "5", "1"], i+a),
           ([t, "1", "1", "9", "1", "5", "3"], i+o),
           ([t, "1", "1", "1", "3", "3", "1"], i+r),          #END easy triangles
           #([t, "-1073741823", "-1073741823", "-1", "1", "1073741823", "1073741823"], i+o),
           ]    

for io in in_outs:
    assert(subprocess.Popen(io[0], stdout=subprocess.PIPE).communicate()[0] == io[1])

print "all tests passed"
