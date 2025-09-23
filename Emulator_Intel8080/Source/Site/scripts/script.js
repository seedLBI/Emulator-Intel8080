let MobilePopupMenu = document.querySelector(".mobile-popup-window");
let ButtonMobilePopupMenu = document.querySelector("#button-mobile-popup-window");
ButtonMobilePopupMenu.onclick = function () {
  MobilePopupMenu.classList.toggle('hidden');
}

let mobileButtons = document.querySelectorAll(".mobile-buttons-popup");
for (let index = 0; index < mobileButtons.length; index++) {
  const element = mobileButtons[index];
  element.onclick = function () {
    MobilePopupMenu.classList.add('hidden');
  }
}






const left_box = document.querySelector('.left-box');
const right_box = document.querySelector('.right-box');
const AnchorDownload = document.getElementById('Download');

function ChangePositionWelcomeParts() {
  const posY_AnchorDownload = AnchorDownload.getBoundingClientRect().y + window.scrollY;
  const scrollY = window.scrollY / (posY_AnchorDownload - 300);
  left_box.style.transform = `translateX(${-scrollY * left_box.getBoundingClientRect().width}px)`;
  right_box.style.transform = `translateX(${scrollY * right_box.getBoundingClientRect().width}px)`;
}
ChangePositionWelcomeParts();

window.addEventListener('scroll', () => {ChangePositionWelcomeParts(); });












let circles = document.querySelectorAll(".circle");
let circlesSelected;
circles[0].classList.toggle("selected")
circlesSelected = circles[0];
let currentID_image = 0;

let image_screenshots = document.getElementById("Image")


function addIndexCurrentID() {
  if (currentID_image === 3)
    ChangeCircleImage(0);
  else
    ChangeCircleImage(currentID_image + 1);
}

function subIndexCurrentID() {
  if (currentID_image === 0)
    ChangeCircleImage(3);
  else
    ChangeCircleImage(currentID_image - 1);
}

function ChangeCircleImage(index) {

  if (index === currentID_image) return;

  circlesSelected.classList.toggle("selected");
  let temp = circlesSelected;
  circlesSelected = circles[index];
  circlesSelected.classList.toggle("selected");
  circles[index] = temp;

  image_screenshots.classList.add("fade");
  setTimeout(() => {
    currentID_image = index;
    let url_image = `url("img/screenshot_${currentID_image + 1}.png")`;
    image_screenshots.style.backgroundImage = url_image;
    image_screenshots.classList.remove("fade");
  }, 200);

}


for (let index = 0; index < circles.length; index++) {
  circles[index].addEventListener('click', () => { ChangeCircleImage(index); });
}

document.getElementById("LeftSkipImage").addEventListener('click', () => { subIndexCurrentID(); });
document.getElementById("RightSkipImage").addEventListener('click', () => { addIndexCurrentID(); });


let autoSlideInterval;
let imageBlock = document.getElementById("ImageBlock");

function startAutoSlide() {
  autoSlideInterval = setInterval(addIndexCurrentID, 1500);
}

imageBlock.addEventListener('mouseenter', () => clearInterval(autoSlideInterval));
imageBlock.addEventListener('mouseleave', startAutoSlide);

startAutoSlide();





const DownloadButton = document.querySelector(".ButtonDownload");
const leftBox_DownloadButton = document.querySelector(".LeftBox-ButtonDownload");

DownloadButton.addEventListener('mouseenter', () => leftBox_DownloadButton.classList.add("hover"));
DownloadButton.addEventListener('mouseleave', () => leftBox_DownloadButton.classList.remove("hover"));
