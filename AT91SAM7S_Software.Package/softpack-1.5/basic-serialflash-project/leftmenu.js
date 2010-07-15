function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5510\" class=\"headerLeftMenuInActive\"><a id=\"aID5510\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_serialflashmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-serialflash-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5628\" class=\"leftMenuInActive\"><a id=\"aID5628\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
