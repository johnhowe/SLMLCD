function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5462\" class=\"headerLeftMenuInActive\"><a id=\"aID5462\" href=\"#\" OnMouseOver=\"link('_dir','async0',this)\" class=\"leftMenuLinkHeadInActive\">async</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
