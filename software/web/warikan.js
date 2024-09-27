// https://script.google.com/macros/s/AKfycbzPY2-duPx8ulvGl_dih_2Bd6YkCM-_1mYczR9Kt_mdMP98EOxXuqXPVz9jad6kngLD/exec
// https://script.google.com/macros/s/AKfycbxKSF9JKvL_SDS5dTjkAMfCU733gTm8JErSNHKzQyThQhUNWuIv6uCZLN05rsIg8tKD/exec

fetch('https://script.google.com/macros/s/AKfycbxKSF9JKvL_SDS5dTjkAMfCU733gTm8JErSNHKzQyThQhUNWuIv6uCZLN05rsIg8tKD/exec')
  .then(response => response.json())
  .then(data => console.log(data))
  .catch(error => console.log("error: ", error));