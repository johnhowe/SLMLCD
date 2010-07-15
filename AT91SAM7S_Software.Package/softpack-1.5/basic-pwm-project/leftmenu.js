function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5507\" class=\"headerLeftMenuInActive\"><a id=\"aID5507\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_pwmmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-pwm-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5625\" class=\"leftMenuInActive\"><a id=\"aID5625\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
