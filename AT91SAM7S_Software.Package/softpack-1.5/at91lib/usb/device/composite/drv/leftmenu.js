function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5493\" class=\"headerLeftMenuInActive\"><a id=\"aID5493\" href=\"#\" OnMouseOver=\"link('_dir','drv0',this)\" class=\"leftMenuLinkHeadInActive\">drv</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
