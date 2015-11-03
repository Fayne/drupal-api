
var isMobile={Android:function(){return navigator.userAgent.match(/Android/i);},BlackBerry:function(){return navigator.userAgent.match(/BlackBerry/i);},iOS7:function(){return navigator.userAgent.match(/iPhone OS 7/i);},iOS8:function(){return navigator.userAgent.match(/iPhone OS 8/i);},iOS9:function(){return navigator.userAgent.match(/iPhone OS 9/i);},Windows:function(){return navigator.userAgent.match(/IEMobile/i);},any:function(){return(isMobile.Android()||isMobile.BlackBerry()||isMobile.iOS7()||isMobile.iOS8()||isMobile.iOS9()||isMobile.Windows());}};

function showContent(x){
		if (navigator.language.match(/en/i)){var lang="en";} else if (navigator.language.match(/cn/i)){var lang="cn";}
		if (x==8){
			document.getElementById("header").setAttribute("src", "i/iOS8-"+lang+"_header.png");
			document.getElementById("spacer1").setAttribute("height", "0");
			document.getElementById("hdr1").setAttribute("src", "i/iOS8-"+lang+"_hdr1.png");
			document.getElementById("hdr1").setAttribute("width", "90%");
			document.getElementById("png1").setAttribute("src", "i/iOS8-"+lang+"_png1.jpg");
			document.getElementById("hdr2").setAttribute("src", "i/iOS8-"+lang+"_hdr2.png");
			document.getElementById("hdr2").setAttribute("width", "90%");
			document.getElementById("png2").setAttribute("src", "i/iOS8-"+lang+"_png2.png");
			document.getElementById("png2").setAttribute("width", "65%");
			document.getElementById("hdr3").setAttribute("src", "i/iOS8-"+lang+"_hdr3.png");
			document.getElementById("hdr3").setAttribute("width", "90%");
			document.getElementById("png3").setAttribute("src", "i/iOS8-"+lang+"_png3.j");
			document.getElementById("png3").setAttribute("width", "65%");
			document.getElementById("hdr4").setAttribute("src", "i/iOS8-"+lang+"_hdr4.png");
			document.getElementById("hdr4").setAttribute("width", "90%");
			document.getElementById("png4").style.display = "none";
			document.getElementById("hdr5").style.display = "none";
			document.getElementById("png5").style.display = "none";
			document.getElementById("hdr6").style.display = "none";
			document.getElementById("png6").style.display = "none";
			document.getElementById("hdr7").style.display = "none";
			document.getElementById("png7").style.display = "none";
			document.getElementById("hdr8").style.display = "none";
			document.getElementById("png8").style.display = "none";
		}
		if (x==9){
			document.getElementById("header").setAttribute("src", "i/iOS9-"+lang+"_header.png");
			document.getElementById("hdr1").setAttribute("src", "i/iOS9-"+lang+"_hdr1.png");
			document.getElementById("png1").setAttribute("src", "i/iOS9-"+lang+"_png1.jpg");
			document.getElementById("hdr2").setAttribute("src", "i/iOS9-"+lang+"_hdr2.png");
			document.getElementById("png2").setAttribute("src", "i/iOS9-"+lang+"_png2.png");
			document.getElementById("hdr3").setAttribute("src", "i/iOS9-"+lang+"_hdr3.jpg");
			document.getElementById("png3").setAttribute("src", "i/iOS9-"+lang+"_png3.png");
			document.getElementById("hdr4").setAttribute("src", "i/iOS9-"+lang+"_hdr4.jpg");
			document.getElementById("png4").setAttribute("src", "i/iOS9-"+lang+"_png4.png");
			document.getElementById("hdr5").setAttribute("src", "i/iOS9-"+lang+"_hdr5.jpg");
			document.getElementById("png5").setAttribute("src", "i/iOS9-"+lang+"_png5.png");
			document.getElementById("hdr6").setAttribute("src", "i/iOS9-"+lang+"_hdr6.jpg");
			document.getElementById("png6").setAttribute("src", "i/iOS9-"+lang+"_png6.png");
			document.getElementById("hdr7").setAttribute("src", "i/iOS9-"+lang+"_hdr7.jpg");
			document.getElementById("png7").setAttribute("src", "i/iOS9-"+lang+"_png7.png");
			document.getElementById("hdr8").setAttribute("src", "i/iOS9-"+lang+"_hdr8.png");
			document.getElementById("png8").setAttribute("src", "i/iOS9-"+lang+"_png8.png");
		}
		if (x==0) {
			document.getElementById("header").setAttribute("src", "i/Android-"+lang+"_header.png");
			document.getElementById("spacer1").style.display = "none";
			document.getElementById("hdr1").setAttribute("src", "i/Android-"+lang+"_hdr1.png");
			document.getElementById("hdr1").setAttribute("width", "90%");
			document.getElementById("png1").setAttribute("src", "i/Android-"+lang+"_png1.jpg");
			document.getElementById("hdr2").setAttribute("src", "i/Android-"+lang+"_hdr2.png");
			document.getElementById("hdr2").setAttribute("width", "90%");
			document.getElementById("png2").setAttribute("src", "i/Android-"+lang+"_png2.png");
			document.getElementById("png2").setAttribute("width", "65%");
			document.getElementById("hdr3").setAttribute("src", "i/Android-"+lang+"_hdr3.png");
			document.getElementById("hdr3").setAttribute("width", "90%");
			document.getElementById("png3").setAttribute("src", "i/Android-"+lang+"_png3.jpg");
			document.getElementById("png3").setAttribute("width", "65%");
			document.getElementById("hdr4").setAttribute("src", "i/Android-"+lang+"_hdr4.png");
			document.getElementById("hdr4").setAttribute("width", "90%");
			document.getElementById("png4").setAttribute("src", "i/Android-"+lang+"_png4.png");
			document.getElementById("png4").setAttribute("width", "65%");
			document.getElementById("hdr5").setAttribute("src", "i/Android-"+lang+"_hdr5.png");
			document.getElementById("hdr5").setAttribute("width", "90%");
			document.getElementById("png5").setAttribute("src", "i/Android-"+lang+"_png5.jpg");
			document.getElementById("png5").setAttribute("width", "65%");
			document.getElementById("hdr6").style.display = "none";
			document.getElementById("png6").style.display = "none";
			document.getElementById("hdr7").style.display = "none";
			document.getElementById("png7").style.display = "none";
			document.getElementById("hdr8").style.display = "none";
			document.getElementById("png8").style.display = "none";
		}