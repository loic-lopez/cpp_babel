#Protocol
If magicode is false or a packet timestamp is before a precedent packet timestamp then ignore packet


struct Packet:
```
int magiccode ('0x1337')
int timestamp
char cmd (200 = erreur)
```
*Followed by a cmd_struct which will be casted by the client or server depending of the cmd (char cmd)*

struct SoundPacket:
```
int magiccode('0x42')
int timestamp
int size
array[size] char sound
```

*struct plugin*
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
4 -> Invisible (server never sent invisible but disconnected)
```

*struct user_info*:
```
string username (fixe / id)
string pseudo (can be change)
enum status status
string motd
string city
string phone
string mail
string langue
vector struct plugin
```

*struct group_info*
```
int id
string name
vector string user_name
```

*struct message*
```
int id
int timestamp
string msg[900] (1024 + all other fields max to prevent splitting from ethernet card)
bool modified
string username
int group_id
```

##Client to server

AccountCreate: ->
```
string username
string password
```

AccountLogin:
```
string username
string password
```

AccountChangePass:
```
string password
string new_password
```

AccountDelete:
```
None
```

AccountChangePseudo:
```
string new_pseudo
```

AccountChangeStatus:
```
enum status status
```

AccountChangeMOTD:
```
string motd
```

AccountChangeInfo:
```
struct user_info userinfo
```

UserGetAllContactName:
```
None
```

UserGetAllGroupID
```
None
```

UserAddContact:
```
string username
```

UserAcceptContact:
```
string username
```

UserDenyContact:
```
string username
```

UserDelContact:
```
string username
```

UserGetInfoOf:
```
string username
```

UserGetPendingInvite
```
None
```

GroupCreate:
```
array string usernames
```

GroupRename:
```
int group_id
string name
```

GroupAddUser:
```
string username
```

GroupDeleteUser:
```
string username
```

GroupeDelete:
```
int group_id
```

MsgGetUser:
```
string username
int from_id
int nb_msg
```

MsgGetGroup:
```
int group_id
int from_id
int nb_msg
```

MsgTo:
```
struct message msg
```

MsgDelete:
```
int msg_id
```

CallUser:
```
string username
```

CallGroup:
```
int group_id
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

AcceptOnPort:
```
int port (0 = dont accept)
```

##Server to client

SendFriendList
```
vector username
```

SendUserInfo
```
struct user_info info
```

UserCallYou
```
string username
```

UserAcceptedCall
```
string ip
int port
```

UserHasRejectedCall
```
None
```

UserHasHang
```
None
```

UserHasSentMSG
```
struct message msg
```

UserHasSentFriendRequest
```
string username
```

UserHasAcceptedFriend
```
string username
```

UserHasChangeStatus
```
string username
enum status status
```

UserHasChangePseudo
```
string username
string pseudo
```

SendGroupList
```
vector int group_id
```

SendGroupInfo *(Use also when group delete or group rename or someone dc from group)*
```
struct group_info info
```

GroupRemoveYou
```
int group_id;
```

SendHistoryMsg
```
vector struct msg msg;
```

PluginMsg
```
string plugin_name
void *data
int length
```

##ClientToClient

SendAudio = struct SoundPacket audio

##Utils

###Client to server

| Code        | Description |
|:------------:|:---------------:|
| 0 | AccountCreate |
| 1 | AccountLogin |
| 2 | AccountChangePass |
| 3 | AccountDelete |
| 4 | AccountChangePseudo |
| 5 | AccountChangeStatus |
| 6 | AccountChangeMOTD |
| 7 | AccountChangeInfo |
| 20 | UserGetAllContactName |
| 21 | UserAddContact |
| 22 | UserAcceptContact |
| 23 | UserDenyContact |
| 24 | UserDelContact |
| 25 | UserGetInfoOf |
| 26 | UserGetPendingInvite |
| 40 | GroupCreate |
| 41 | GroupGetAllGroupID |
| 42 | GroupGetInfo |
| 43 | GroupAddUser |
| 44 | GroupDeleteUser |
| 45 | GroupRename |
| 46 | GroupeDelete |
| 60 | MsgGetUser |
| 61 | MsgGetGroup |
| 61 | MsgDelete |
| 62 | MsgTo |
| 80 | CallUser |
| 81 | CallGroup |
| 82 | CallHang |
| 83 | CallAcceptOnPort |
| 100 | PluginSendMsg |

###ServerToClient

| Code        | Description |
|:------------:|:---------------:|
| 0 | UserCallYou |
| 1 | UserAcceptedCall  |
| 2 | UserHasRejectedCall |
| 3 | UserHasHang |
| 4 | UserHasSentMSG |
| 5 | UserHasSentFriendRequest |
| 6 | UserHasAcceptedFriend |
| 7 | UserHasChangeStatus |
| 8 | UserHasChangePseudo |
| 9 | SendUserList |
| 10 | SendUserInfo |
| 20 | GroupHasChanged |
| 21 | SendGroupList |
| 22 | GroupDeleted |
| 40 | SendHistoryMsg |
| 60 | PluginMsg |

###ClientToClient

| Code        | Description |
|:------------:|:---------------:|
| 0 | SendAudio |
| 1 | SendVideo |

###Error code:

| Code        | Description |
|:------------:|:---------------:|
| 0 | ok |
| 1 | incorrect login or password format |
| 2 | bad password or login |
| 20 | user already exist |
| 21 | user don't exist *(work also when sending a message to wrong user or not friend user)* |
| 22 | user offline |
| 23 | user is already in group |
| 24 | user is already your friend |
| 40 | group dont exist |
| 60 | message don't exist |
| 61 | can't message yourself |
| 62 | can't modify another user message |
| 80 | can't call yourself |
| 81 | user already in call |
| 100 | unknown error |