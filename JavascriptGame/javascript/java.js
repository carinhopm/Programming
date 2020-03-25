window.onload = function() {
	
    var nav = document.getElementById("main");
    tabs = nav.getElementsByClassName("tab");
    sections = document.getElementsByTagName("section");
    movil_interface = document.getElementsByClassName("movil");
    no_movil = document.getElementsByClassName("no_movil");
    var device = navigator.userAgent;
	
    for (var i=0;i<tabs.length;i++){
		tabs[i].addEventListener("click", activateTab);
    }
	
	if (device.match(/Iphone/i)|| device.match(/Ipod/i)|| device.match(/Android/i)|| device.match(/J2ME/i)|| device.match(/BlackBerry/i)|| device.match(/iPhone|iPad|iPod/i)|| device.match(/Opera Mini/i)|| device.match(/IEMobile/i)|| device.match(/Mobile/i)|| device.match(/Windows Phone/i)|| device.match(/windows mobile/i)|| device.match(/windows ce/i)|| device.match(/webOS/i)|| device.match(/palm/i)|| device.match(/bada/i)|| device.match(/series60/i)|| device.match(/nokia/i)|| device.match(/symbian/i)|| device.match(/HTC/i)) {  
		for (var i=0;i<movil_interface.length;i++){
			movil_interface[i].style.display="block";	
		}
		for (var i=0;i<no_movil.length;i++){
			no_movil[i].style.display="none";	
		}
    }
} 
   
function activateTab(){
    for (var i=0;i<tabs.length;i++){
		var tabClasses = tabs[i].classList;
		var sectionClasses = sections[i].classList;
		if(tabs[i]==this){ //Muestra la pestaña seleccionada
			tabClasses.add("currentab");
			sectionClasses.add("current");
		}else{ //Borra la anterior pestaña mostrada
			tabClasses.remove("currentab");
			sectionClasses.remove("current");
		}
    }
}

function buttons (num){
	for (var i=0;i<tabs.length;i++){
		if(i == num){
		tabs[i].classList.add("currentab");
		sections[i].classList.add ("current");
		}else{
		tabs[i].classList.remove("currentab");
		sections[i].classList.remove("current");
		}
	}
}

function vidplay() {
   var video = document.getElementById("videotutorial");
   video.currentTime = 80;
   video.play();
}