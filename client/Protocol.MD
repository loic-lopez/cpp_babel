#Protocol

If maggicode is false or a packet timestamp is before a precedent packet timestamp then ignore packet


Packet:
```
int magiccode ('0x1337')
int timestamp
char cmd
```
*Followed by a cmd_struct which will be casted by the client or server depending of the cmd (char cmd)*

SoundPacket:
```
int magiccode('0x42')
int size
array[size] char sound
```

##Client to server

*enum plugin*
```
string name
string desc
```

*enum status*:
```
0 -> disconnected
1 -> connected
2 -> busy
3 -> Don't bother
4 -> Invisible
```

*enum user_info*:
```
string username
enum status status
string motd
string city
string phone
int id
array enum plugin
```

*enum group_info*
```
string name
array users
int group_id
```

*enum message*
```
int timestamp
string msg[1000] (1024 + all other fields max to prevent splitting from ethernet card)
bool modified
int from
bool to_group
int to (user_id ou group_id)
```

AccountCreate: -> 
```
username
password
```

AccountLogin:
```
username
password
```

AccountChangePass:
```
password
new_password
```

AccountDelete:
```
None
```

AccountChangeUsername:
```
new_username
```

AccountChangeStatus:
```
status
```

AccountChangeMOTD:
```
motd
```

AccountChangeInfo:
```
enum user_info
```

UserGetAllContactName:
```
None
```

UserAddContact:
```
username
```

UserDelContact:
```
user_id
```

UserGetInfoOf:
```
user_id
```

GroupCreate:
```
user_id
```

GroupRename:
```
group_id
name
```

GroupAddUser:
```
user_id
```

GroupDeleteUser:
```
user_id //TODO USER ID
```

GroupeDelete:
```
group_id
```

MsgGetUser:
```
user_id
```

MsgToUser:
```
enum message msg
```

MsgToGroup:
```
enum message msg
```

MsgModify:
```
int msg_id
string new_msg
```

MsgDelete:
```
int msg_id
```

CallUser:
```
user_id
```

CallGroup:
```
group_id
```

CallHang:
```
None
```

PluginSendMsg:
```
string plugin_name
void *data
int length
```

##Server to client