# RX Warning
A website for looking up the drug-to-drug interactions for all pharmaceuticals. Interactions are grouped by interaction severity and alphabetically sorted by drug names. RX Warning is a very powerful tool for quickly findin some common interacting drugs for your meds. Do not rely on rx-warning alone to determine your meds safety; always consult your physician first!

## Guide
The website can be accessed directly at [rx-warning.com](https://rx-warning.com). Input any drug's (generic) name to get a list of interacting drugs and the severities of those interactions.

Clicking on the Random button at the top forwards to the webpage of interactions for a random drug.

The Advanced Settings section under the searchbar can change the underlyinh data structure used to store the graph of interactions. The differences in speed of the Adjacency List vs the Adjacency Matrix is displayed on the the drug page. When the page is accessed with Adjacency List is selected, the background is red, and when it is Adjacency Matrix, the background is blue.

If there are missing or undefined elements, reset the cookies and cache, and/or do CTRL+SHIFT+R on chrome to troubleshoot.

## Installation
No installation is neccesary to simply access the website, but if you wish to host your own instance of rx-warning for testing and contribution, this is a detailed guide for installing the dependencies and getting the server running on 64-bit Windows.

If these instructions do not apply to you, the general steps should be installing Boost, compiling Boost, installing ASIO standalone headers, and running CMake.

**Ensure you have MSVC 14.3, which should already be set up if you have Visual Studio set up for C++!**

**Make sure you have the latest version of CMake!**

### Set Up Boost

1. Obtain binaries for Boost 1.82 at https://sourceforge.net/projects/boost/files/boost-binaries/1.82.0/boost_1_82_0-msvc-14.3-64.exe (automatic download link)
    - This file can also be found by going through [boost.org](boost.org) > [Downloads (sidebar)](https://www.boost.org/users/download/) > [Prebuilt windows binaries](https://sourceforge.net/projects/boost/files/boost-binaries/) > [1.82.0](https://sourceforge.net/projects/boost/files/boost-binaries/1.82.0/boost_1_82_0-msvc-14.3-64.exe)

2. Run the installation
3. Go into the root Boost folder (which should contain b2.exe and bootstrap.bat) in powershell
4. Run command: `bootstrap`
5. Run command: `.\b2`
6. Finally, go to environment variables and set `Boost_ROOT_DIR` to the directory of your Boost root (same as step 3).

### Set Up ASIO
The easiest way we have found to install boost is through vcpkg. You may skip to step 4 if you already have VCPKG set up.

1. Create an empty directory anywehre on your computer to set up VCPKG, C:/Users/youracct/VCPKG works fine.
2. Open this directory in powershell and clone the VCPKG repo using: `git clone https://github.com/microsoft/vcpkg.git`
3. Run the VCPKG installation with: `cd vcpkg; .\bootstrap-vcpkg.bat`
4. Integrate VCPKG into MSVC with `.\vcpkg.exe integrate install`
5. Install ASIO with `.\vcpkg.exe install asio`

### Set Up VSCode

1. Create an empty directory for rx-warning and clone this repo into it with `git clone https://github.com/Dogantoro/rx-warning.git` on powershell.
2. Open the enclosed rx-warning directory in vscode.
3. Ensure you have the CMake Tools extension installed
4. Go to the CMake tab on the left sidebar.
5. Click on configure and select **x86_amd64**
6. If configure is successful, click the Launch option at the bottom of the window, which should be a singular play button icon.

If CMake cannot find boost, make sure CMake is updated to the **latest** version!

At this point, if everything is set up correctly, the rx-warning server should build and start showing a progress bar of loading CSVs. This process might take a while. Once this is complete, you can access your instance of rx-warning through http://localhost:18080/