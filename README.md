# cognex_camera
driver for communicating with cognex camera COGNEX AlignSight communication interface for both TCP/IP and SLMP/Ethernet-IP connections

a detail description of the driver can be found here
https://support.cognex.com/docs/alignsight_330/web/EN/alignsight-communications/Content/Topics/Communication%20Manual/Overview.htm?tocpath=Overview%7C_____0#_Toc33531049

If you want to use modbus tcp then please go to the full_modbus project i posted elsewhere on github

Ethernet IP (e.g. Allen Bradley / Yasakawa) and Mitsbishi support drivers added

Ive added drivers to a robot (at present kawasaki) which can accept the pose information read from the camera to do object pickup.
