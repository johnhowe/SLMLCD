function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5478\" class=\"headerLeftMenuInActive\"><a id=\"aID5478\" href=\"#\" OnMouseOver=\"link('_dir','pmc0',this)\" class=\"leftMenuLinkHeadInActive\">pmc</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
