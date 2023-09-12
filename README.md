# FindStrongestPasswordCpp
Run `FindStrongestPasswordCpp.exe` console application to test and compare the strength of your passwords. <br />
<sub> Based on the **PasswordStrengthTest** code (Kotlin). Rewrote it in C++ and added new features. Moved from functional programming to OO. </sub>
## Input
Takes a string containing any number of passwords (of any length) separated by any number of white spaces.
## Output
Prints out a comparison table with the following colums:

<table>
  <tr>
    <td> <b>Score</b> </td>
    <td>The rows in the table are sorted by score. The score is calculated based on the data in the comparison table.</td>
  </tr>
  
  <tr>
    <td><b>Password</b></td>
    <td>A password entered by user. </td>
  </tr>
  
  <tr>
    <td><b>Length</b></td>
    <td>The length of the password.</td>
  </tr>

  <tr>
    <td><b>SP Chars</b></td>
    <td>The number of special (not alphanumeric) characters in the password.</td>
  </tr>

  <tr>
    <td><b>Digits</b></td>
    <td>Indicates whether the password contains at least 1 digit (+). It remains empty if there are no digits.</td>
  </tr>

  <tr>
    <td><b>LCase</b></td>
    <td>Indicates whether the password contains at least 1 lower case character (+). It remains empty if there are no lower case characters.</td>
  </tr>

  <tr>
    <td><b>UCase</b></td>
    <td>Indicates whether the password contains at least 1 upper case character (+). It remains empty if there are no upper case characters.</td>
  </tr>

  <tr>
    <td><b>Patters</b></td>
    <td>Common patterns found in the password. The number of patterns negatively affects the score.</td>
  </tr>
  
</table>

### Common pattern search algorithms
The application relies on 5 algorithms in order to detect the following common password patterns:
* Sequences of any repeating characters
* Sequences of repeating pairs of characters
* Sequences of letters in (reverse) alphabetical order
* Arithmetic sequences with common differences of 1 or -1
* Common passwords, such as "iloveyou", "password", etc.
  
Only sequences longer than 3 characters are taken into account. The search algorithms are not case-sensitive.
## Sample input and output
### Example 1
**Input:** `ADmINadmin PA$$w0rD1234 QWERTY007 password`<br />
**Output:**<br />
![Comparison table 1](/readme_img/table1.jpg)
### Example 2
**Input:** `AbcdEf76543        3456ZYxW   `<br />
**Output:**<br />
![Comparison table 1](/readme_img/table2.jpg)
### Example 3
**Input:** `1111PasssworD    hahahaHA678 hi+++++bye 565656StoP____ `<br />
**Output:**<br />
![Comparison table 3](/readme_img/table3.jpg)
