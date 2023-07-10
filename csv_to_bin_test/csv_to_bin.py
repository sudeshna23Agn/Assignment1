import csv
from struct import *
import sys, os


# DEBUG = False

# def pinfo(*args, **kwargs):
#     if DEBUG:
#         print(*args, file=sys.stderr, **kwargs)
phase_id = dict()
sequence_id = dict()
command_id = dict()
enum_list = []
"""is it possible to create new dictionary at run time?"""

#open the main csv file to be read
fp = open('sequence_list.csv', 'r')
heading = next(fp)              #read the first row to identify the fields
enum_list = heading.split(',')       #stores the enums into list
for i in range(len(enum_list)-1):
    enum_list[i] += '.csv'               #load the enum csv file
    print(enum_list[i])
    with open(enum_list[i],mode = 'r') as fl:    #open the enum csv file
        heading = next(fl)                  
        csvFile = csv.reader(fl)
        dict_to_add = enum_list[i][:(len(enum_list[i])-4)]
        print(dict_to_add)
        for lines in csvFile:              
            eval(dict_to_add)[lines[0]] = lines[1]   #load the enum csv into a dictionary
# print(phase_id)
# print(sequence_id)
# print(command_id)

"""bin file name is same as the structure name in  c <struct.bin>, 
 in this file the bytes arrays will be stored from the csv file"""

#reading the commands from csv file
main_csvFile = csv.reader(fp)
no_of_fields = len(enum_list)-1
bytes_stream = bytearray()
print("number of fileds in the main csv file: ",no_of_fields) 
for lines in main_csvFile:
    for i in range (0,no_of_fields):
        field_value = 0
        enum_str = enum_list[i][:(len(enum_list[i])-4)]
        print(enum_list[i][:(len(enum_list[i])-4)])
        field_value = eval(enum_str)[lines[i]]
        print(field_value)
        bytes_stream.extend(pack("<B",int(field_value)))
    print(bytes_stream)


binary_file = open("engine_sequence_struct.bin", "wb")
binary_file.write(bytes_stream)
binary_file.close()




