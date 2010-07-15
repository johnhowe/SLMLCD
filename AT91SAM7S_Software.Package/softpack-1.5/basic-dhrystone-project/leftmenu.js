function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5504\" class=\"headerLeftMenuInActive\"><a id=\"aID5504\" href=\"#\" OnMouseOver=\"link('_dir','basicmi_dhrystonemi_project0',this)\" class=\"leftMenuLinkHeadInActive\">basic-dhrystone-project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5622\" class=\"leftMenuInActive\"><a id=\"aID5622\" href=\"#\" OnMouseOver=\"link('_unit','main_c0',this)\" class=\"leftMenuLinkInActive\">main.c</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
