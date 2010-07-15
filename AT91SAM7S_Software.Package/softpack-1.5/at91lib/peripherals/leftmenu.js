function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5475\" class=\"headerLeftMenuInActive\"><a id=\"aID5475\" href=\"#\" OnMouseOver=\"link('_dir','peripherals0',this)\" class=\"leftMenuLinkHeadInActive\">peripherals</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5469\" class=\"leftMenuInActive\"><a id=\"aID5469\" href=\"#\" OnMouseOver=\"link('_dir','adc/adc0',this)\" class=\"leftMenuLinkInActive\">adc</a></div>\n");
document.write("<div id=\"divID5470\" class=\"leftMenuInActive\"><a id=\"aID5470\" href=\"#\" OnMouseOver=\"link('_dir','aic/aic0',this)\" class=\"leftMenuLinkInActive\">aic</a></div>\n");
document.write("<div id=\"divID5471\" class=\"leftMenuInActive\"><a id=\"aID5471\" href=\"#\" OnMouseOver=\"link('_dir','cp15/cp150',this)\" class=\"leftMenuLinkInActive\">cp15</a></div>\n");
document.write("<div id=\"divID5472\" class=\"leftMenuInActive\"><a id=\"aID5472\" href=\"#\" OnMouseOver=\"link('_dir','dbgu/dbgu0',this)\" class=\"leftMenuLinkInActive\">dbgu</a></div>\n");
document.write("<div id=\"divID5473\" class=\"leftMenuInActive\"><a id=\"aID5473\" href=\"#\" OnMouseOver=\"link('_dir','eefc/eefc0',this)\" class=\"leftMenuLinkInActive\">eefc</a></div>\n");
document.write("<div id=\"divID5474\" class=\"leftMenuInActive\"><a id=\"aID5474\" href=\"#\" OnMouseOver=\"link('_dir','efc/efc0',this)\" class=\"leftMenuLinkInActive\">efc</a></div>\n");
document.write("<div id=\"divID5476\" class=\"leftMenuInActive\"><a id=\"aID5476\" href=\"#\" OnMouseOver=\"link('_dir','pio/pio0',this)\" class=\"leftMenuLinkInActive\">pio</a></div>\n");
document.write("<div id=\"divID5477\" class=\"leftMenuInActive\"><a id=\"aID5477\" href=\"#\" OnMouseOver=\"link('_dir','pit/pit0',this)\" class=\"leftMenuLinkInActive\">pit</a></div>\n");
document.write("<div id=\"divID5478\" class=\"leftMenuInActive\"><a id=\"aID5478\" href=\"#\" OnMouseOver=\"link('_dir','pmc/pmc0',this)\" class=\"leftMenuLinkInActive\">pmc</a></div>\n");
document.write("<div id=\"divID5479\" class=\"leftMenuInActive\"><a id=\"aID5479\" href=\"#\" OnMouseOver=\"link('_dir','pwmc/pwmc0',this)\" class=\"leftMenuLinkInActive\">pwmc</a></div>\n");
document.write("<div id=\"divID5480\" class=\"leftMenuInActive\"><a id=\"aID5480\" href=\"#\" OnMouseOver=\"link('_dir','rtt/rtt0',this)\" class=\"leftMenuLinkInActive\">rtt</a></div>\n");
document.write("<div id=\"divID5481\" class=\"leftMenuInActive\"><a id=\"aID5481\" href=\"#\" OnMouseOver=\"link('_dir','spi/spi0',this)\" class=\"leftMenuLinkInActive\">spi</a></div>\n");
document.write("<div id=\"divID5482\" class=\"leftMenuInActive\"><a id=\"aID5482\" href=\"#\" OnMouseOver=\"link('_dir','tc/tc0',this)\" class=\"leftMenuLinkInActive\">tc</a></div>\n");
document.write("<div id=\"divID5483\" class=\"leftMenuInActive\"><a id=\"aID5483\" href=\"#\" OnMouseOver=\"link('_dir','twi/twi0',this)\" class=\"leftMenuLinkInActive\">twi</a></div>\n");
document.write("<div id=\"divID5484\" class=\"leftMenuInActive\"><a id=\"aID5484\" href=\"#\" OnMouseOver=\"link('_dir','usart/usart0',this)\" class=\"leftMenuLinkInActive\">usart</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
