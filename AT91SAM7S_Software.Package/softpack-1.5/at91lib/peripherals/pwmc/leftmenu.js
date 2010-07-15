function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5479\" class=\"headerLeftMenuInActive\"><a id=\"aID5479\" href=\"#\" OnMouseOver=\"link('_dir','pwmc0',this)\" class=\"leftMenuLinkHeadInActive\">pwmc</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5545\" class=\"leftMenuInActive\"><a id=\"aID5545\" href=\"#\" OnMouseOver=\"link('_unit','pwmc_h0',this)\" class=\"leftMenuLinkInActive\">pwmc.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
