Problem 1: Banking – Distributed Account Verification 
System 
Scenario 
A bank operates multiple ATM kiosks connected to a central validation server. Each ATM 
must verify account details and balance before processing transactions. 
Requirements 
● The central server maintains account records on disk. 
● Multiple ATM clients send account verification requests concurrently. 
● The server must respond quickly even during peak hours. 
● Failed or invalid requests must be logged persistently. 
● Some operations are critical, while others are informational. 
Constraints / Hints 
● Pax must decide: 
○ Which requests require guaranteed delivery 
○ Which can tolerate occasional packet loss 
● Server must support multiple simultaneous clients 
● Account data is stored in files, not a database 
● Efficient lookup is required 
Expected Thinking Areas 
● TCP vs UDP decision 
● Use of STL containers (map, vector, list) 
● File locking / synchronization 
● Request–response protocol design 
● Error handling and logging