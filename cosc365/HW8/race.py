# Noah Morris
# nmorri11

import threading
import time
import random

# Runner class
class Runner(threading.Thread):
    def __init__(self, number):
        # values for contestant number, section number, and total time taken for previous sections
        self.contestant = number
        self.section = 1
        self.timeTaken = 0
        
        threading.Thread.__init__(self)
    
    # run function for starting the thread
    def run(self):
        # runner thread runs until the runner has gotten passed section 4
        while self.section != 5:
            # gets a random time between 10 and 100 seconds uses sleep to go through that time, then increments the time taken and section number
            sectionTime = random.uniform(10,100)
            time.sleep(sectionTime)
            self.timeTaken += sectionTime
            self.section += 1
        
# Reporter class
class Reporter(threading.Thread):
    def __init__(self):
        # list for runners and finished runners as well as a value for the start time
        self.runningRunners = []
        self.finishedRunners = []
        self.startTime = 0

        threading.Thread.__init__(self)
    
    # run function for starting the thread
    def run(self):
        # adds a runner for every number 1-999 to running runners
        for i in range(1,1000):
            self.runningRunners.append(Runner(i))

        # records the start time and starts the race for every racer by running their thread
        self.startTime = time.time()
        for i in self.runningRunners:
            i.start()
        
        # opens the ReporterUpdates file for reporting every 2 seconds until every runner has finished the race
        reporterFile = open("ReporterUpdates.txt", "w+")

        # results at time:0 is outside of the loop so that there is not a sleep call before being called
        reporterFile.write("Results at time:0\n")
        reporterFile.write("----------------------------------------------------------\n")
        reporterFile.write("| Contestant  #  | Section | Section Time | Overall Time |\n")

        # grabs the current time and prints the initial times for all of the runners
        currentTime = time.time()
        for i in self.runningRunners:
            reporterFile.write("| Contestant "+ str(i.contestant).zfill(3))
            reporterFile.write(" |    1    | ")
            reporterFile.write("{:.8f}".format(currentTime - self.startTime).ljust(12) + " | ")
            reporterFile.write("{:.8f}".format(currentTime - self.startTime).ljust(12) + " |\n")
        reporterFile.write("----------------------------------------------------------\n")

        # set result time to 2 for the first print in the loop
        resultTime = 2

        # runs the race until there are no more active racers running
        while len(self.runningRunners) != 0:
            # sleep for 2 seconds and obtain the current time
            time.sleep(2)
            currentTime = time.time()

            # prints the header lines for the contestants with the current time
            reporterFile.write("Results at time:" + str(resultTime) + "\n")
            reporterFile.write("----------------------------------------------------------\n")
            reporterFile.write("| Contestant  #  | Section | Section Time | Overall Time |\n")
            
            # prints the values for every currently running contestant
            for i in self.runningRunners:
                reporterFile.write("| Contestant "+ str(i.contestant).zfill(3) +  " |   ")

                # set the section to end if their section is equal to 5 and prints out the time since they finished and the total time the runner ran
                if i.section == 5:
                    reporterFile.write("End   | ")
                    reporterFile.write("{:.8f}".format((currentTime - self.startTime) - i.timeTaken).ljust(12) + " | ")
                    reporterFile.write("{:.8f}".format(i.timeTaken).ljust(12) + " |\n")
                # else print the section the runner is currently in, the time spent in the current section, and the total time raced so far
                else:
                    reporterFile.write(" " + str(i.section) + "    | ")
                    reporterFile.write("{:.8f}".format((currentTime - self.startTime) - i.timeTaken).ljust(12) + " | ")
                    reporterFile.write("{:.8f}".format(currentTime - self.startTime).ljust(12) + " |\n")
            reporterFile.write("----------------------------------------------------------\n")

            # removes any runner that has finished the race
            for i in self.runningRunners:
                if not i.is_alive():
                    self.runningRunners.remove(i)
                    self.finishedRunners.append(i)

            # updates the results time by 2
            resultTime += 2

        # closes the reporter file and opens the results file
        reporterFile.close()
        resultsFile = open("FinalResults.txt", "w+")

        # sorts the finished runners to make sure that racers that finished within the same recorded interval are recorded properly in the results
        sorted = 0
        while sorted == 0:
            # goes through the list using bubble sort to sort the list based on the timeTaken values
            sorted = 1
            for i in range(len(self.finishedRunners)):
                # skips the final index
                if self.finishedRunners[i] == self.finishedRunners[len(self.finishedRunners) - 1]:
                    break

                # sorts if needed
                if self.finishedRunners[i].timeTaken > self.finishedRunners[i+1].timeTaken:
                    temp = self.finishedRunners[i]
                    self.finishedRunners[i] = self.finishedRunners[i+1]
                    self.finishedRunners[i+1] = temp
                    sorted = 0

        # sets total time to 0 and prints out the two header lines
        totalTime = 0
        resultsFile.write("---------------------------------\n")
        resultsFile.write("| Contestant  #  | Overall Time |\n")

        # prints out the contest number and how long they took to race in order from fastest to slowest
        for i in self.finishedRunners:
            resultsFile.write("| Contestant "+ str(i.contestant).zfill(3) + " | ")
            resultsFile.write("{:.8f}".format(i.timeTaken).ljust(12) + " |\n")

            # increments total time to compile every runner's time
            totalTime += i.timeTaken

        # prints out the final two lines including the overall time spent
        resultsFile.write("---------------------------------\n")
        resultsFile.write("Overall, the runners spent " + str(round((totalTime),8)) + " seconds running total.\n")
        resultsFile.close()

def main():
    # declares and starts the reporter race thread
    race = Reporter()
    race.start()

if __name__=="__main__":
    main()