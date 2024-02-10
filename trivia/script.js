// Part 1: Multiple-choice trivia question
const option1 = document.getElementById("option1");
const option2 = document.getElementById("option2");
const option3 = document.getElementById("option3");

option1.addEventListener("click", handleAnswer);
option2.addEventListener("click", handleAnswer);
option3.addEventListener("click", handleAnswer);

function handleAnswer(event) {
  const selectedOption = event.target;

  if (selectedOption === option2) {
    selectedOption.classList.add("correct");
    displayResult("Correct!");
  } else {
    selectedOption.classList.add("incorrect");
    displayResult("Incorrect");
  }

  disableButtons();
}

// Part 2: Text-based free response question
const answerInput = document.getElementById("answerInput");
const confirmButton = document.getElementById("confirmButton");

confirmButton.addEventListener("click", checkAnswer);

function checkAnswer() {
  const userAnswer = answerInput.value.toLowerCase();
  const correctAnswer = "leonardo da vinci";

  if (userAnswer === correctAnswer) {
    answerInput.classList.add("correct");
    displayResult("Correct!");
  } else {
    answerInput.classList.add("incorrect");
    displayResult("Incorrect");
  }

  answerInput.disabled = true;
  confirmButton.disabled = true;
}

// Helper function to display the result
function displayResult(result) {
  const resultText = document.createElement("p");
  resultText.textContent = result;
  document.body.appendChild(resultText);
}

// Helper function to disable all option buttons
function disableButtons() {
  option1.disabled = true;
  option2.disabled = true;
  option3.disabled = true;
}
