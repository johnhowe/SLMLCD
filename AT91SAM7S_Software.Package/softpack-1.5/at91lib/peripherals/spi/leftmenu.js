function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5481\" class=\"headerLeftMenuInActive\"><a id=\"aID5481\" href=\"#\" OnMouseOver=\"link('_dir','spi0',this)\" class=\"leftMenuLinkHeadInActive\">spi</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5345\" class=\"leftMenuInActive\"><a id=\"aID5345\" href=\"#\" OnMouseOver=\"link('_page','SPIconfigurationmacros0',this)\" class=\"leftMenuLinkInActive\">SPI configuration macros</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
