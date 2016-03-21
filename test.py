from datetime import date
import tornado.escape
import tornado.ioloop
import tornado.web
import mysql.connector

class ScoreHandler(tornado.web.RequestHandler):
    def get(self):
        print("get")

        # Get our configuration data from the helper function
        # so we can use the MySQL-Python connector
        configDict = self.get_config()
        config = configDict["config"]
        cnx = configDict["cnx"]
        cursor = configDict["cursor"]

        # Define our MySQL query
        # Get all the names from the 'scoreTable' table
        query = ("SELECT name, score from scoreTable ")
        cursor.execute(query)

        nameList = []
        scoreList = []
        highscoreList = []
        highscoreDict = dict()

        # Get the selected values from the cursor
        # Values are 'tuples' so we convert to string
        for u in cursor:
            nameList.append(str(u[0]))
            scoreList.append(int(u[1]))

        # Dictionary
        index = 0
        for n in nameList:
            highscoreDict[n] = scoreList[index]
            index+=1

        # Sort dictionary(Returns list of tuples)
        highscoreList = sorted(highscoreDict.items(), key=lambda x:x[1])

        # Reverse list so highest score is first
        highscoreList.reverse()

        # Only have top 10 in list
        while(len(highscoreList) > 10):
            highscoreList.pop()

        print("********************************************")
        print(highscoreList)
        print("********************************************")

        # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        # Put back into dictionary
        highscoreDict = {}
        for h in highscoreList:
            highscoreDict[h[0]] = h[1]

        print(highscoreDict)
        self.write(highscoreDict)

    def post(self):
        name = self.get_argument('name', '')
        score = self.get_argument('score', '')
        print(name)
        print(score)

        # Get our configuration data from the helper function
        # so we can use the MySQL-Python connector
        configDict = self.get_config()
        config = configDict["config"]
        cnx = configDict["cnx"]
        cursor = configDict["cursor"]

        query = ("INSERT INTO scoreTable "
                "(name, score)"
                "VALUES (%(name)s, %(score)s)")

        data_user = {
        'name': name,
        'score': score
        }

        cursor.execute(query, data_user)

        # Make sure data is committed to the database
        cnx.commit()

    def get_config(self):
        """ get_config helper function
        Sorts configuration for the MySQL database
        """
        config = {
        'user': 'root',
        'password': 'mysql',
        'host': '127.0.0.1',
        'database': 'FYPDB'
        }

        cnx = mysql.connector.connect(**config)
        cursor = cnx.cursor()

        configDict = dict()
        configDict["config"] = config
        configDict["cnx"] = cnx
        configDict["cursor"] = cursor

        return configDict
 
application = tornado.web.Application([
    (r"/score", ScoreHandler)
])
 
if __name__ == "__main__":
    application.listen(443)
    tornado.ioloop.IOLoop.instance().start()