local ver = myModuleVersion()
if isloaded("gpu") then
  load("hpctoolkit/" .. ver .. "-gpu")
elseif isloaded("cpu") then
  load("hpctoolkit/" .. ver .. "-cpu")
else
  LmodError("Please load either the cpu or gpu module first")
end
