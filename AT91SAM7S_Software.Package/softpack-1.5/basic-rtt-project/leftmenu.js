function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5508\" class=\"headerLeftMenuInActive\"><a id=\"aID5508\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_rttmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-rtt-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5626\" class=\"leftMenuInActive\"><a id=\"aID5626\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
