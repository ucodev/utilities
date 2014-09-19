#!/usr/bin/python

import pyodbc

# Connect
#
# NOTE: For any other database engine, you need to change the DRIVER= variable in order to match
#       a configuration tag in the /etc/odbcinst.ini
#
#       Oracle connection string requires the DBQ= variable
#
#	SQLServer connection string requires the TDS_Version= variable
#	(use TDS_Version=8.0 for MSSQL2012
#

#conn = pyodbc.connect("DRIVER=Oracle11g;DBQ=//127.0.0.1:1521/dbname;UID=system;PWD=secret")
#conn = pyodbc.connect("DRIVER=MSSQL;SERVER=127.0.0.1;PORT=3306;DATABASE=dbname;UID=administrator;PWD=secret;TDS_Version=8.0")

conn = pyodbc.connect("DRIVER=MySQL;SERVER=127.0.0.1;PORT=3306;DATABASE=mysql;UID=root;PWD=secret")


## From now on, the interface is similar to MySQLdb

# Cursor
cursor = conn.cursor()

# Query
query = cursor.execute("SELECT * FROM user")

# Fetch
row = query.fetchone()

# Show
print row

# Close
cursor.close()
conn.close()

