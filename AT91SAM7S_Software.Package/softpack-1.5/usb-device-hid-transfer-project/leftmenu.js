function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5523\" class=\"headerLeftMenuInActive\"><a id=\"aID5523\" href=\"#\" OnMouseOver=\"link('_dir','usbmi_devicemi_hidmi_transfermi_project0',this)\" class=\"leftMenuLinkHeadInActive\">usb-device-hid-transfer-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5522\" class=\"leftMenuInActive\"><a id=\"aID5522\" href=\"#\" OnMouseOver=\"link('_dir','HIDTest/HIDTest0',this)\" class=\"leftMenuLinkInActive\">HIDTest</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5640\" class=\"leftMenuInActive\"><a id=\"aID5640\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
