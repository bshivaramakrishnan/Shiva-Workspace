#powershell script tutorial
#simple output: 
Write-Host "Hello,Powershell"

#Variables :

$name = "Shiva"
Write-Host $name " This is a string data type"

$num1 = 20
$num2 = 30
$sum =  $num1+$num2
Write-Host "Addition of two numbers 20 and 30 :  " $sum

#Array

$parts = @("Brake","Chain","Motor","Engine")

#Hash
$details = @{
    name = "Shiva"
    Age = 22
}

#Comparision Operators

$num1 -eq $num2  #equal
$num1 -ne $num2  #Not Equal
$num1 -gt $num2  #greater than
$num1 -lt $num2  #less Than

Write-Host "Logical -and"
#logical and
($num1 -ne $num2) -and ($num1 -lt $num2)

#logical or 
Write-Host "Logical -Or"
($num1 -ne $num2) -or ($num1 -lt $num2)

#Conditional Statement
if($num1 -eq $num2){
    write-host "num1 = num2"
}
elseif($num1 -ne $num2)
{
    Write-Host "num1 != num2"
}
else 
{
    Write-Host "Error"
}

#For Loop Printing Numbers upto 10
for($i = 0 ; $i -le 10 ; $i++)
{
    Write-Host "For Iterator Number : $i"
}

#foreach Loop
foreach($part in $parts)
{
    Write-Host "foreach Iterator Part : $part"
}

#While Loop
$i=0
while($i -le 10)
{
    Write-Host "While Loop Iterator $i"
    $i++
}

#Writing a function 

function displayname ($name)
{
    Write-Host "Executing Function : $name"
}
displayname Shiva  #Function Call 

#Error Handling 

try
{
    get-item "C:\nonexistent.txt"-ErrorAction Stop  #Powbe called powerShell only handles Termination Error so for Non Terminating Error use -ErrorAction Stop , Else Catch block wont execute
}
catch
{
    Write-Host "Error Occured "
}
finally
{
    Write-Host "Always Run "
}

#Working with Files and Directories
# List files
Get-ChildItem "C:\Test"

# Read file
Get-Content "C:\Test\sample.txt"

# Write file
Set-Content "C:\Test\new.txt" -Value "Hello from PowerShell!"

# Append file
Add-Content "C:\Test\new.txt" -Value "`nNew Line"

# Rename file
Rename-Item "C:\Test\new.txt" -NewName "renamed.txt"

# Delete file
Remove-Item "C:\Test\renamed.txt"
