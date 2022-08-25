# ビルドスクリプト
$current = Get-Location
try {
  Set-Location ($current.Path)
  MSBuild.exe .\windowsDesktop\OpenSiv3D.sln
  "*****　ビルド完了　*****"
} catch {
  $_
} finally {
  Set-Location $current.Path
}
