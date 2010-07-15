function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5511\" class=\"headerLeftMenuInActive\"><a id=\"aID5511\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_twimi_eeprommi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-twi-eeprom-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5629\" class=\"leftMenuInActive\"><a id=\"aID5629\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
