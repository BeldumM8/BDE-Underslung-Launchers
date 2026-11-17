class BDE_USL_WeaponDefinition
{
    string ClassName;
    string GroupName;
    bool SupportsM203;
    bool SupportsGP25;
    bool SupportsSix12;
    bool SupportsFN40;
    bool SupportsUSL;

    void BDE_USL_WeaponDefinition(string className, string groupName, bool supportsM203, bool supportsGP25, bool supportsSix12, bool supportsFN40, bool supportsUSL)
    {
        ClassName = className;
        GroupName = groupName;
        SupportsM203 = supportsM203;
        SupportsGP25 = supportsGP25;
        SupportsSix12 = supportsSix12;
        SupportsFN40 = supportsFN40;
        SupportsUSL = supportsUSL;
    }
};

class BDE_USL_WeaponSetting
{
    string ClassName;
    int M203Enabled = 1;
    int GP25Enabled = 1;
    int Six12Enabled = 1;
    int FN40Enabled = 1;
    int USLEnabled = 1;
};


class BDE_USL_LegacyWeaponSetting
{
    string ClassName;
    int M203Enabled = 1;
    int GP25Enabled = 1;
};

class BDE_USL_LegacyCompatibilitySettingsFile
{
    int ConfigVersion = 1;
    ref array<ref BDE_USL_LegacyWeaponSetting> Weapons = new array<ref BDE_USL_LegacyWeaponSetting>;
};

class BDE_USL_CompatibilitySettingsFile
{
    int ConfigVersion = 1;
    ref array<ref BDE_USL_WeaponSetting> Weapons = new array<ref BDE_USL_WeaponSetting>;
};

class BDE_USL_VOG25GrenadeSettingsFile
{
    int ConfigVersion = 1;
    int AllowStandard40mmRounds = 0;
};

class BDE_USL_SettingsManager
{
    static const string SETTINGS_ROOT = "$profile:BDE/UnderSlungLaunchers/";
    static const string VOG25_GRENADE_SETTINGS = "$profile:BDE/UnderSlungLaunchers/VOG25_Grenades.json";
    static const string LEGACY_GP25_GRENADE_SETTINGS = "$profile:BDE/UnderSlungLaunchers/GP25_Grenades.json";
    static const int SETTINGS_VERSION = 3;

    protected static ref TStringArray s_DisabledM203;
    protected static ref TStringArray s_DisabledGP25;
    protected static ref TStringArray s_DisabledSix12;
    protected static ref TStringArray s_DisabledFN40;
    protected static ref TStringArray s_DisabledUSL;
    protected static bool s_AllowStandard40mmRounds;
    protected static bool s_ServerInitialized;
    protected static bool s_ClientSyncReceived;

    protected static void EnsureRuntimeArrays()
    {
        if (!s_DisabledM203)
            s_DisabledM203 = new TStringArray;

        if (!s_DisabledGP25)
            s_DisabledGP25 = new TStringArray;

        if (!s_DisabledSix12)
            s_DisabledSix12 = new TStringArray;

        if (!s_DisabledFN40)
            s_DisabledFN40 = new TStringArray;

        if (!s_DisabledUSL)
            s_DisabledUSL = new TStringArray;
    }

    static void InitializeServer()
    {
        if (!GetGame().IsServer())
            return;

        EnsureRuntimeArrays();
        s_DisabledM203.Clear();
        s_DisabledGP25.Clear();
        s_DisabledSix12.Clear();
        s_DisabledFN40.Clear();
        s_DisabledUSL.Clear();
        s_AllowStandard40mmRounds = false;

        MakeDirectory("$profile:BDE");
        MakeDirectory("$profile:BDE/UnderSlungLaunchers");

        array<ref BDE_USL_WeaponDefinition> definitions = BuildDefinitions();
        TStringArray groupNames = new TStringArray;

        foreach (BDE_USL_WeaponDefinition definition : definitions)
        {
            if (!definition || definition.GroupName == "")
                continue;

            if (groupNames.Find(definition.GroupName) == -1)
                groupNames.Insert(definition.GroupName);
        }

        groupNames.Sort();

        foreach (string groupName : groupNames)
            LoadMergeAndSaveGroup(groupName, definitions);

        LoadAndSaveVOG25GrenadeSettings();
        s_ServerInitialized = true;
    }

    protected static bool ConfigClassIsKindOf(string configRoot, string className, string targetBase)
    {
        if (configRoot == "" || className == "" || targetBase == "")
            return false;

        string currentClass = className;

        for (int depth = 0; depth < 32; depth++)
        {
            if (currentClass == targetBase)
                return true;

            string baseClass;

            if (!GetGame().ConfigGetBaseName(configRoot + " " + currentClass, baseClass) || baseClass == "" || baseClass == currentClass)
                return false;

            currentClass = baseClass;
        }

        return false;
    }

    protected static array<ref BDE_USL_WeaponDefinition> BuildDefinitions()
    {
        array<ref BDE_USL_WeaponDefinition> definitions = new array<ref BDE_USL_WeaponDefinition>;
        string cfgRoot = "CfgWeapons";
        int weaponCount = GetGame().ConfigGetChildrenCount(cfgRoot);

        for (int weaponIndex = 0; weaponIndex < weaponCount; weaponIndex++)
        {
            string weaponClass;
            GetGame().ConfigGetChildName(cfgRoot, weaponIndex, weaponClass);

            if (weaponClass == "")
                continue;

            string weaponPath = cfgRoot + " " + weaponClass;
            string compatiblePath = weaponPath + " BDE_USL_Compatible";

            if (!GetGame().ConfigIsExisting(compatiblePath) || GetGame().ConfigGetInt(compatiblePath) != 1)
                continue;

            string scopePath = weaponPath + " scope";

            if (!GetGame().ConfigIsExisting(scopePath) || GetGame().ConfigGetInt(scopePath) != 2)
                continue;

            string groupPath = weaponPath + " BDE_USL_SettingsGroup";

            if (!GetGame().ConfigIsExisting(groupPath))
                continue;

            string groupName;
            GetGame().ConfigGetText(groupPath, groupName);

            if (groupName == "")
                continue;

            TStringArray launcherTypes = new TStringArray;
            string launcherTypesPath = weaponPath + " BDE_USL_Types";

            if (!GetGame().ConfigIsExisting(launcherTypesPath))
                continue;

            GetGame().ConfigGetTextArray(launcherTypesPath, launcherTypes);

            bool supportsM203 = false;
            bool supportsGP25 = false;
            bool supportsSix12 = false;
            bool supportsFN40 = false;
            bool supportsUSL = false;

            foreach (string launcherType : launcherTypes)
            {
                if (ConfigClassIsKindOf("CfgWeapons", launcherType, "BDE_OTS14_Launcher"))
                {
                    supportsUSL = true;
                    continue;
                }

                if (ConfigClassIsKindOf("CfgWeapons", launcherType, "BDE_FN40"))
                {
                    supportsFN40 = true;
                    continue;
                }

                if (ConfigClassIsKindOf("CfgWeapons", launcherType, "BDE_Six12"))
                {
                    supportsSix12 = true;
                    continue;
                }

                if (ConfigClassIsKindOf("CfgWeapons", launcherType, "BDE_GP25"))
                {
                    supportsGP25 = true;
                    continue;
                }

                if (ConfigClassIsKindOf("CfgWeapons", launcherType, "BDE_M203"))
                    supportsM203 = true;
            }

            if (!supportsM203 && !supportsGP25 && !supportsSix12 && !supportsFN40 && !supportsUSL)
                continue;

            definitions.Insert(new BDE_USL_WeaponDefinition(weaponClass, groupName, supportsM203, supportsGP25, supportsSix12, supportsFN40, supportsUSL));
        }

        return definitions;
    }

    protected static void LoadMergeAndSaveGroup(string groupName, array<ref BDE_USL_WeaponDefinition> definitions)
    {
        TStringArray classNames = new TStringArray;
        map<string, ref BDE_USL_WeaponDefinition> definitionByClass = new map<string, ref BDE_USL_WeaponDefinition>;

        foreach (BDE_USL_WeaponDefinition groupDefinition : definitions)
        {
            if (!groupDefinition || groupDefinition.GroupName != groupName)
                continue;

            if (definitionByClass.Contains(groupDefinition.ClassName))
                continue;

            definitionByClass.Set(groupDefinition.ClassName, groupDefinition);
            classNames.Insert(groupDefinition.ClassName);
        }

        if (classNames.Count() == 0)
            return;

        classNames.Sort();
        string filePath = SETTINGS_ROOT + groupName + ".json";
        BDE_USL_CompatibilitySettingsFile existingSettings = new BDE_USL_CompatibilitySettingsFile;

        if (FileExist(filePath))
            JsonFileLoader<BDE_USL_CompatibilitySettingsFile>.JsonLoadFile(filePath, existingSettings);

        if (!existingSettings)
            existingSettings = new BDE_USL_CompatibilitySettingsFile;

        if (!existingSettings.Weapons)
            existingSettings.Weapons = new array<ref BDE_USL_WeaponSetting>;

        bool legacyPerLauncherSettings = existingSettings.ConfigVersion < 2;
        map<string, ref BDE_USL_LegacyWeaponSetting> legacyByClass = new map<string, ref BDE_USL_LegacyWeaponSetting>;

        if (legacyPerLauncherSettings && FileExist(filePath))
        {
            BDE_USL_LegacyCompatibilitySettingsFile legacySettingsFile = new BDE_USL_LegacyCompatibilitySettingsFile;
            JsonFileLoader<BDE_USL_LegacyCompatibilitySettingsFile>.JsonLoadFile(filePath, legacySettingsFile);

            if (legacySettingsFile && legacySettingsFile.Weapons)
            {
                foreach (BDE_USL_LegacyWeaponSetting legacySetting : legacySettingsFile.Weapons)
                {
                    if (!legacySetting || legacySetting.ClassName == "")
                        continue;

                    legacyByClass.Set(legacySetting.ClassName, legacySetting);
                }
            }
        }

        map<string, ref BDE_USL_WeaponSetting> existingByClass = new map<string, ref BDE_USL_WeaponSetting>;

        foreach (BDE_USL_WeaponSetting existingSetting : existingSettings.Weapons)
        {
            if (!existingSetting || existingSetting.ClassName == "")
                continue;

            existingByClass.Set(existingSetting.ClassName, existingSetting);
        }

        BDE_USL_CompatibilitySettingsFile mergedSettings = new BDE_USL_CompatibilitySettingsFile;
        mergedSettings.ConfigVersion = SETTINGS_VERSION;

        foreach (string className : classNames)
        {
            BDE_USL_WeaponDefinition classDefinition = definitionByClass.Get(className);

            if (!classDefinition)
                continue;

            BDE_USL_WeaponSetting mergedSetting = existingByClass.Get(className);

            if (!mergedSetting)
                mergedSetting = new BDE_USL_WeaponSetting;

            int legacyM203Enabled = 1;
            int legacyGP25Enabled = 1;
            BDE_USL_LegacyWeaponSetting legacyClassSetting = legacyByClass.Get(className);

            if (legacyClassSetting)
            {
                legacyM203Enabled = NormalizeToggle(legacyClassSetting.M203Enabled);
                legacyGP25Enabled = NormalizeToggle(legacyClassSetting.GP25Enabled);
            }

            mergedSetting.ClassName = className;

            if (classDefinition.SupportsM203)
            {
                if (legacyPerLauncherSettings)
                    mergedSetting.M203Enabled = legacyM203Enabled;
                else
                    mergedSetting.M203Enabled = NormalizeToggle(mergedSetting.M203Enabled);

                if (mergedSetting.M203Enabled == 0 && s_DisabledM203.Find(className) == -1)
                    s_DisabledM203.Insert(className);
            }
            else
            {
                mergedSetting.M203Enabled = 1;
            }

            if (classDefinition.SupportsGP25)
            {
                if (legacyPerLauncherSettings)
                    mergedSetting.GP25Enabled = legacyGP25Enabled;
                else
                    mergedSetting.GP25Enabled = NormalizeToggle(mergedSetting.GP25Enabled);

                if (mergedSetting.GP25Enabled == 0 && s_DisabledGP25.Find(className) == -1)
                    s_DisabledGP25.Insert(className);
            }
            else
            {
                mergedSetting.GP25Enabled = 1;
            }

            if (classDefinition.SupportsSix12)
            {
                if (legacyPerLauncherSettings)
                    mergedSetting.Six12Enabled = 1;
                else
                    mergedSetting.Six12Enabled = NormalizeToggle(mergedSetting.Six12Enabled);

                if (mergedSetting.Six12Enabled == 0 && s_DisabledSix12.Find(className) == -1)
                    s_DisabledSix12.Insert(className);
            }
            else
            {
                mergedSetting.Six12Enabled = 1;
            }

            if (classDefinition.SupportsFN40)
            {
                if (legacyPerLauncherSettings)
                    mergedSetting.FN40Enabled = NormalizeToggle(legacyM203Enabled);
                else
                    mergedSetting.FN40Enabled = NormalizeToggle(mergedSetting.FN40Enabled);

                if (mergedSetting.FN40Enabled == 0 && s_DisabledFN40.Find(className) == -1)
                    s_DisabledFN40.Insert(className);
            }
            else
            {
                mergedSetting.FN40Enabled = 1;
            }

            if (classDefinition.SupportsUSL)
            {
                if (legacyPerLauncherSettings)
                    mergedSetting.USLEnabled = NormalizeToggle(legacyGP25Enabled);
                else
                    mergedSetting.USLEnabled = NormalizeToggle(mergedSetting.USLEnabled);

                if (mergedSetting.USLEnabled == 0 && s_DisabledUSL.Find(className) == -1)
                    s_DisabledUSL.Insert(className);
            }
            else
            {
                mergedSetting.USLEnabled = 1;
            }

            mergedSettings.Weapons.Insert(mergedSetting);
        }

        SaveGroupFile(filePath, mergedSettings, definitionByClass);
    }

    protected static void LoadAndSaveVOG25GrenadeSettings()
    {
        BDE_USL_VOG25GrenadeSettingsFile settings = new BDE_USL_VOG25GrenadeSettingsFile;

        if (FileExist(VOG25_GRENADE_SETTINGS))
        {
            JsonFileLoader<BDE_USL_VOG25GrenadeSettingsFile>.JsonLoadFile(VOG25_GRENADE_SETTINGS, settings);
        }
        else if (FileExist(LEGACY_GP25_GRENADE_SETTINGS))
        {
            JsonFileLoader<BDE_USL_VOG25GrenadeSettingsFile>.JsonLoadFile(LEGACY_GP25_GRENADE_SETTINGS, settings);
        }

        if (!settings)
            settings = new BDE_USL_VOG25GrenadeSettingsFile;

        settings.ConfigVersion = SETTINGS_VERSION;
        settings.AllowStandard40mmRounds = NormalizeToggle(settings.AllowStandard40mmRounds);
        s_AllowStandard40mmRounds = settings.AllowStandard40mmRounds == 1;
        JsonFileLoader<BDE_USL_VOG25GrenadeSettingsFile>.JsonSaveFile(VOG25_GRENADE_SETTINGS, settings);

        if (FileExist(LEGACY_GP25_GRENADE_SETTINGS) && FileExist(VOG25_GRENADE_SETTINGS))
            DeleteFile(LEGACY_GP25_GRENADE_SETTINGS);
    }

    protected static int NormalizeToggle(int value)
    {
        if (value == 0)
            return 0;

        return 1;
    }

    protected static void SaveGroupFile(string filePath, BDE_USL_CompatibilitySettingsFile settings, map<string, ref BDE_USL_WeaponDefinition> definitionByClass)
    {
        if (!settings || !settings.Weapons)
            return;

        FileHandle fileHandle = OpenFile(filePath, FileMode.WRITE);

        if (!fileHandle)
            return;

        FPrintln(fileHandle, "{");
        FPrintln(fileHandle, "    \"ConfigVersion\": " + SETTINGS_VERSION.ToString() + ",");
        FPrintln(fileHandle, "    \"Weapons\": [");

        int settingCount = settings.Weapons.Count();

        for (int settingIndex = 0; settingIndex < settingCount; settingIndex++)
        {
            BDE_USL_WeaponSetting setting = settings.Weapons[settingIndex];

            if (!setting)
                continue;

            BDE_USL_WeaponDefinition definition = definitionByClass.Get(setting.ClassName);

            if (!definition)
                continue;

            TStringArray toggleLines = new TStringArray;

            if (definition.SupportsM203)
                toggleLines.Insert("\"M203Enabled\": " + setting.M203Enabled.ToString());

            if (definition.SupportsGP25)
                toggleLines.Insert("\"GP25Enabled\": " + setting.GP25Enabled.ToString());

            if (definition.SupportsSix12)
                toggleLines.Insert("\"Six12Enabled\": " + setting.Six12Enabled.ToString());

            if (definition.SupportsFN40)
                toggleLines.Insert("\"FN40Enabled\": " + setting.FN40Enabled.ToString());

            if (definition.SupportsUSL)
                toggleLines.Insert("\"USLEnabled\": " + setting.USLEnabled.ToString());

            FPrintln(fileHandle, "        {");
            FPrintln(fileHandle, "            \"ClassName\": \"" + setting.ClassName + "\",");

            int toggleCount = toggleLines.Count();

            for (int toggleIndex = 0; toggleIndex < toggleCount; toggleIndex++)
            {
                string toggleLine = "            " + toggleLines[toggleIndex];

                if (toggleIndex < toggleCount - 1)
                    toggleLine += ",";

                FPrintln(fileHandle, toggleLine);
            }

            string closingLine = "        }";

            if (settingIndex < settingCount - 1)
                closingLine += ",";

            FPrintln(fileHandle, closingLine);
        }

        FPrintln(fileHandle, "    ]");
        FPrintln(fileHandle, "}");
        CloseFile(fileHandle);
    }

    static bool IsLauncherEnabled(string weaponClass, EntityAI launcher)
    {
        if (GetGame().IsServer() && !s_ServerInitialized)
            InitializeServer();

        EnsureRuntimeArrays();

        if (weaponClass == "" || !launcher)
            return true;

        if (launcher.IsKindOf("BDE_OTS14_Launcher"))
            return s_DisabledUSL.Find(weaponClass) == -1;

        if (launcher.IsKindOf("BDE_FN40"))
            return s_DisabledFN40.Find(weaponClass) == -1;

        if (launcher.IsKindOf("BDE_Six12"))
            return s_DisabledSix12.Find(weaponClass) == -1;

        if (launcher.IsKindOf("BDE_GP25"))
            return s_DisabledGP25.Find(weaponClass) == -1;

        if (launcher.IsKindOf("BDE_M203"))
            return s_DisabledM203.Find(weaponClass) == -1;

        return true;
    }

    static bool IsVOG25MagazineAllowed(Magazine magazine)
    {
        if (!magazine)
            return false;

        return IsVOG25MagazineTypeAllowed(magazine.GetType());
    }

    static bool IsVOG25MagazineTypeAllowed(string magazineType)
    {
        if (magazineType == "")
            return false;

        if (ConfigClassIsKindOf("CfgMagazines", magazineType, "Ammo_VOG25"))
            return true;

        if (!ConfigClassIsKindOf("CfgMagazines", magazineType, "Ammo_40mm_Base"))
            return false;

        if (GetGame().IsServer() && !s_ServerInitialized)
            InitializeServer();

        return s_AllowStandard40mmRounds;
    }

    static bool IsVOG25AmmoTypeAllowed(string ammoType)
    {
        if (ammoType == "")
            return false;

        if (ammoType == "Bullet_VOG25")
            return true;

        bool standard40mm = ammoType == "Bullet_40mm_Explosive" || ammoType == "Bullet_40mm_ChemGas" || ammoType == "Bullet_40mm_Smoke_Red" || ammoType == "Bullet_40mm_Smoke_Green" || ammoType == "Bullet_40mm_Smoke_White" || ammoType == "Bullet_40mm_Smoke_Black";

        if (!standard40mm)
            return false;

        if (GetGame().IsServer() && !s_ServerInitialized)
            InitializeServer();

        return s_AllowStandard40mmRounds;
    }

    static bool IsGP25MagazineAllowed(Magazine magazine)
    {
        return IsVOG25MagazineAllowed(magazine);
    }

    static bool IsGP25AmmoTypeAllowed(string ammoType)
    {
        return IsVOG25AmmoTypeAllowed(ammoType);
    }

    protected static string BuildDisabledPayload(TStringArray disabledClasses)
    {
        string payload = "";

        if (!disabledClasses)
            return payload;

        foreach (string disabledClass : disabledClasses)
        {
            if (disabledClass == "")
                continue;

            if (payload != "")
                payload += ";";

            payload += disabledClass;
        }

        return payload;
    }

    static void SendSettingsToClient(PlayerBase player, PlayerIdentity identity)
    {
        if (!GetGame().IsServer() || !player || !identity)
            return;

        if (!s_ServerInitialized)
            InitializeServer();

        EnsureRuntimeArrays();
        string disabledM203Payload = BuildDisabledPayload(s_DisabledM203);
        string disabledGP25Payload = BuildDisabledPayload(s_DisabledGP25);
        string disabledSix12Payload = BuildDisabledPayload(s_DisabledSix12);
        string disabledFN40Payload = BuildDisabledPayload(s_DisabledFN40);
        string disabledUSLPayload = BuildDisabledPayload(s_DisabledUSL);
        int allowStandard40mmRounds = 0;

        if (s_AllowStandard40mmRounds)
            allowStandard40mmRounds = 1;

        Param6<string, string, string, string, string, int> settingsData = new Param6<string, string, string, string, string, int>(disabledM203Payload, disabledGP25Payload, disabledSix12Payload, disabledFN40Payload, disabledUSLPayload, allowStandard40mmRounds);
        GetGame().RPCSingleParam(player, BDE_USL_RPC.BDE_USL_RPC_SETTINGS_SYNC, settingsData, true, identity);
    }

    protected static void ApplyDisabledPayload(string payload, TStringArray disabledClasses)
    {
        disabledClasses.Clear();
        TStringArray parsedClasses = new TStringArray;

        if (payload != "")
            payload.Split(";", parsedClasses);

        foreach (string className : parsedClasses)
        {
            if (className != "" && disabledClasses.Find(className) == -1)
                disabledClasses.Insert(className);
        }
    }

    static void ApplyClientSettings(string disabledM203Payload, string disabledGP25Payload, string disabledSix12Payload, string disabledFN40Payload, string disabledUSLPayload, int allowStandard40mmRounds)
    {
        if (!GetGame().IsClient())
            return;

        EnsureRuntimeArrays();
        ApplyDisabledPayload(disabledM203Payload, s_DisabledM203);
        ApplyDisabledPayload(disabledGP25Payload, s_DisabledGP25);
        ApplyDisabledPayload(disabledSix12Payload, s_DisabledSix12);
        ApplyDisabledPayload(disabledFN40Payload, s_DisabledFN40);
        ApplyDisabledPayload(disabledUSLPayload, s_DisabledUSL);
        s_AllowStandard40mmRounds = allowStandard40mmRounds != 0;
        s_ClientSyncReceived = true;
    }
};
