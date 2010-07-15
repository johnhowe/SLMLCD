function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5509\" class=\"headerLeftMenuInActive\"><a id=\"aID5509\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_sdmi_spimi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-sd-spi-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5627\" class=\"leftMenuInActive\"><a id=\"aID5627\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
