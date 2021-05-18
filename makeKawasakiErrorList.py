# ===================================================================================
#
# python case tool for generating the c code / python script needed for error listing
# all possible errors from the kawasaki robot
#
# ===================================================================================

if __name__ == '__main__':

start_state_for_error = 10

# Using readlines() read the error description index we made using the tesseract ocr
file1 = open('/mnt/c/linuxmirror/Test2.txt', 'r')
Lines = file1.readlines()
 
count = start_state_for_error
# ~~~~~~~~~ print the header file in C ~~~~~~~~~~~~~~~~~~~~~~~
newline = []
for line in Lines:
    line1 = line.split(' ')
    #line1 = line1.replace('\n', '')
    firstfield=line1.pop(0)
	
    # Now just concatenate the strings together and add whitespace between
    finalString = ""
    for i in line1:
        if (i != '\n'):
            finalString += i+" "
    count += 1
    print('#define KAWA_ERROR_%s "(%s) %s"\n' % (firstfield,firstfield,finalString))
    print('#define KAWA_SET_ERROR_%s_STATE %uu' % (firstfield,count))

# ~~~~~~~ print the C code checks ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
newline = []
for line in Lines:
    line1 = line.split(' ')
    firstfield=line1.pop(0)	
    print('else if (strncmp(&rob->feedbackError,KAWA_ERROR_%s,strlen(KAWA_ERROR_%s)) == 0u)' % (firstfield,firstfield))	
    print('{')
    print('    rob->state = KAWA_SET_ERROR_%s_STATE;' % firstfield)
    print('}')
	
# ~~~~~~~ print the header file in python ~~~~~~~~~~~~~~~~~~~~~~~
newline = []
for line in Lines:
    line1 = line.split(' ')
    #line1 = line1.replace('\n', '')
    firstfield=line1.pop(0)
	
    # Now just concatenate the strings together and add whitespace between
    finalString = ""
    for i in line1:
        if (i != '\n'):
            finalString += i+" "
    count += 1
    print('KAWA_ERROR_%s = (\'(%s) %s\')' % (firstfield,firstfield,finalString))

# ~~~~~~~ print the python code checks ~~~~~~~~~~~~~~~~~~~~~~~~~
newline = []
for line in Lines:
    line1 = line.split(' ')
    firstfield=line1.pop(0)	
    print('elif (feedback_error == const.KAWA_ERROR_%s):' % (firstfield))	
    print('    rospy.logerr(feedback_error)')
    print('    return False')
