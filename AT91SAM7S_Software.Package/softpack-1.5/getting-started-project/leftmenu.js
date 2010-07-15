function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5513\" class=\"headerLeftMenuInActive\"><a id=\"aID5513\" href=\"#\" OnMouseOver=\"link('_dir','gettingmi_startedmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">getting-started-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5631\" class=\"leftMenuInActive\"><a id=\"aID5631\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
