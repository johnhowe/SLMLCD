function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5524\" class=\"headerLeftMenuInActive\"><a id=\"aID5524\" href=\"#\" OnMouseOver=\"link('_dir','usbmi_devicemi_massstoragemi_project0',this)\" class=\"leftMenuLinkHeadInActive\">usb-device-massstorage-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5641\" class=\"leftMenuInActive\"><a id=\"aID5641\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}