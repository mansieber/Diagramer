# Introduction
Diagramer is a tool for the visualization of data in form of points in a 2-dimensional plane. The data are send to Diagramer via a TCP connection. 
# Connection
Diagramer acts as a TCP server. It receives connection requests via port 6178. Only one TCP client can connect to Diagramer.
# Data format
Data are sent by TCP clients in form of text strings. The general format is 
**command argument1, argument2, ...**
# Commands

