function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5503\" class=\"headerLeftMenuInActive\"><a id=\"aID5503\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_dataflashmi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-dataflash-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5621\" class=\"leftMenuInActive\"><a id=\"aID5621\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}